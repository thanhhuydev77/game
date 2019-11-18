#include "Panther.h"



Panther::Panther(float X, float Y, int Direction, float autoGoX_Distance, CGameObject * simon)
{
	
	LoadResourceHelper::Loadspritefromfile("content\\characters\\enemies\\panther_sprite.txt", ID_TEX_PANTHER);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\enemies\\panther_ani.txt", this);

	LoadResourceHelper::Loadspritefromfile("content\\effect\\flame_sprite.txt", ID_TEX_FLAME);
	LoadResourceHelper::Loadanimationfromfile("content\\effect\\flame_ani.txt", this);

	Health = 1;
	vx = vy = 0;
	nx = Direction;
	x = X;
	y = Y;
	AutoGoX_Backup_X = x;
	AutoGoX_Distance = autoGoX_Distance;

	isSitting = 1;
	isRunning = 0;
	isJumping = 0;
	isStart = 0;
	isAutoGoX = 0;

	this->simon = simon;
	state = ENEMY_STATE_LIVE;
}

bool Panther::GetIsStart()
{
	return isStart;
}

void Panther::start_disappear()
{
	disappearing = true;
	disappear_start = GetTickCount();
}

void Panther::takedamage()
{
	state = ENEMY_STATE_DIE;
	start_disappear();
	vx = 0;
}

void Panther::Jump()
{
	if (isJumping == true)
		return;
	vy = -PANTHER_VYJUMP;
	vx = PANTHER_VXJUMP * nx;
	isJumping = true;
}

void Panther::Run()
{
	vx = PANTHER_SPEED_RUNNING * nx;
	isRunning = true;
}

Panther::~Panther()
{
}

void Panther::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (isJumping)
	{
		dx = vx * dt;
		dy = vy * dt;
		vy += PANTHER_GRAVITY_JUMPING * dt;
	}
	else
		vy += PANTHER_GRAVITY * dt;// Simple fall down
	if (disappearing)
	{
		if (GetTickCount() - disappear_start > 300)
		{
			disappearing = false;
			disappear_start = 0;
			Health -= 1;
			if (subItem != nullptr)
				subItem->SetState(ITEM_STATE_ACTIVE);
		}
	}
	float DistanceLimit;
	if (nx == 1)
		DistanceLimit = 177;
	else
		DistanceLimit = 130;
	if (isStart == 0 && abs(simon->getx() -x) <= DistanceLimit)
	{
		isSitting = false;
		isRunning = true;
		// chuyển qua trạng thái chạy
		Run();
		isStart = 1;
		isAutoGoX = 1;
	}
	if (abs(x - simon->getx()) > 2000)
	{
		takedamage();
	}
	/*if (isRunning)
		Run();*/
#pragma region collision with ground

	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CInvisibleObject*>(coObjects->at(i)) && dynamic_cast<CInvisibleObject*>(coObjects->at(i))->Gettype() == Const_Value::Brick)
		{
			listObject_Brick.push_back(coObjects->at(i));
		}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	CalcPotentialCollisions(&listObject_Brick, coEvents); // Lấy danh sách các va chạm 
	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		x += dx;
		if (ny == -1)
			y += min_ty * dy + ny * 0.4f;
		if (ny == -1)
		{
			vy = 0; 
			if (isJumping)
			{
				isJumping = false; // kết thúc nhảy
				if (x < simon->getx()) // simon ở bên phải
				{
					this->nx = 1; // đổi hướng panther qua phải 
				}
				else
				{
					this->nx = -1; // đổi hướng panther qua trái
				}
				Run();
			}
			//vx = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

#pragma endregion
	if (isAutoGoX == true)
	{
		if (abs(x - AutoGoX_Backup_X) >= AutoGoX_Distance)
		{
			x = x - (abs(x - AutoGoX_Backup_X) - AutoGoX_Distance);
			isAutoGoX = false;
			vx = 0;

			Jump(); // Sau khi chạy xong thì nhảy

		}
	}
	
}

void Panther::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y+5;
	right = left + PANTHER_BBOX_WIDTH;
	bottom = top + PANTHER_BBOX_HEIGHT;
}

void Panther::Render()
{
	if (Health <= 0)
		return;
	/*if (disappearing)
		animations[1]->Render(x + 7, y + 7, 255);
	else*/
	if (disappearing)
	{
		animations[3]->Render(x + 20, y, 255);
	}
	else
	{
		if (isRunning)
			animations[1]->Render(x, y, 255, nx);
		if (isSitting)
			animations[0]->Render(x, y, 255, nx);
		if (isJumping)
			animations[2]->Render(x, y, 255, nx);
		RenderBoundingBox();
	}
}
