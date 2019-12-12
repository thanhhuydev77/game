#include "Holy_Water.h"



Holy_Water::Holy_Water(CGameObject * owner)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\Holywater\\holywater_sprites.txt", ID_TEX_HOLYWATER);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\Holywater\\holywater_ani.txt", this);
	state = WEPOND_STATE_UNACTIVE;
	this->owner = owner;
	isfinish = true;
}


Holy_Water::~Holy_Water()
{
}

void Holy_Water::UpdatePositionRelateToObject(DWORD dt)
{
	float x1, y1, x2, y2;
	D3DXVECTOR2 newposition;
	owner->GetBoundingBox(x1, y1, x2, y2);
	level = owner->getlevel();
	nx = owner->GetDirect();
	newposition = { x1,y1 + 5 };
	this->SetPosition(newposition.x, newposition.y);
}

void Holy_Water::start_disappear()
{
	fallen = true;
	disappearing = true;
	disappear_start = GetTickCount();
}

void Holy_Water::StartAttack()
{
	if (!isfinish)
		return;
	isfinish = false;
	UpdatePositionRelateToObject(dt);
	state = WEPOND_STATE_ACTIVE;
	vx = HOLYWATER_SPEED_X * nx;
	vy = -HOLYWATER_SPEED_Y;
	Sound::getInstance()->play("holywater", false, 1);
}

void Holy_Water::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (!Camera::getInstance()->checkInCamera(x, y, x + HOLYWATER_BBOX_WIDTH, y + HOLYWATER_BBOX_HEIGHT))
	{
		isfinish = true;
	}
	if (isfinish)
	{
		state = WEPOND_STATE_UNACTIVE;
		return;
	}
	vy += HOLYWATER_GRAVITY * dt;
	if (fallen)
	{
		if (GetTickCount() - disappear_start > 2000)
		{
			disappearing = false;
			disappear_start = 0;
			state = WEPOND_STATE_UNACTIVE;
			isfinish = true;
			fallen = false;
			return;
		}
		else
		{
			
			dx = 0;
			dy = 0;
			return;
		}
	}
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
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		{
			if (nx != 0 || ny != 0)
			{
				start_disappear();
				
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
		delete coEvents[i];

#pragma endregion
	
}

void Holy_Water::reset()
{
	state = WEPOND_STATE_UNACTIVE;
	isfinish = true;
}

void Holy_Water::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == WEPOND_STATE_ACTIVE)
	{
		left = x;
		top = y;

		right = left + HOLYWATER_BBOX_WIDTH;
		bottom = top + HOLYWATER_BBOX_HEIGHT;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Holy_Water::Render()
{
	if (state == WEPOND_STATE_ACTIVE)
	{
		if (fallen)
			animations[1]->Render(x, y, 255, nx);//
		else
			animations[0]->Render(x, y, 255, nx);//
		RenderBoundingBox();
	}
}
