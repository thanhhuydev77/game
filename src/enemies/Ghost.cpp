#include "Ghost.h"



Ghost::Ghost(float X, float Y, int Direction)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\enemies\\Ghost_sprite.txt", ID_TEX_GHOST);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\enemies\\Ghost_ani.txt", this);

	LoadResourceHelper::Loadspritefromfile("content\\effect\\flame_sprite.txt", ID_TEX_FLAME);
	LoadResourceHelper::Loadanimationfromfile("content\\effect\\flame_ani.txt", this);
	x = X;
	y = Y;
	nx = Direction;
	Health = 1;
	vx = GHOST_SPEED_X * Direction;
	state = ENEMY_STATE_LIVE;
}


Ghost::~Ghost()
{
}

void Ghost::start_disappear()
{
	disappearing = true;
	disappear_start = GetTickCount();
}

void Ghost::takedamage()
{ 
	state = ENEMY_STATE_DIE;
	start_disappear();
	vx = 0;
}

void Ghost::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);
	vy += GHOST_GRAVITY * dt;
	if (disappearing)
	{
		if (GetTickCount() - disappear_start > 300)
		{
			disappearing = false;
			disappear_start = 0;
			Health -= 1;
			if(subItem != nullptr)
				subItem->SetState(ITEM_STATE_ACTIVE);
			
			//delete(this);
		}
	}
	float t, l, r, b;
	GetBoundingBox(l, t, r, b);
	RECT check;
	check.left = l;
	check.top = t;
	check.right = r;
	check.bottom = b;
	// still in camera
	if (!Camera::getInstance()->checkInCamera(check))
		Health = 0;
	vector<LPGAMEOBJECT> listObject_Brick;
	listObject_Brick.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
		if (dynamic_cast<CInvisibleObject*>(coObjects->at(i)) && dynamic_cast<CInvisibleObject*>(coObjects->at(i))->Gettype() == Const_Value::Brick)
			listObject_Brick.push_back(coObjects->at(i));

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
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (nx != 0)
		{
			vx *= -1;
			this->nx *= -1;
		}

		if (ny != 0)
		{
			vy = 0;
			//vx = 0;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

}

void Ghost::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + GHOST_BBOX_WIDTH;
	bottom = top + GHOST_BBOX_HEIGHT;
}

void Ghost::Render()
{
	if (Health <= 0)
		return;
	if (disappearing)
		animations[1]->Render(x + 7, y + 7, 255);
	else
		animations[0]->Render(x, y, 255, nx);
	RenderBoundingBox();
}
