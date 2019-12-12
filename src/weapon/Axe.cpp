#include "Axe.h"



Axe::Axe(CGameObject * owner)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\Axe\\Axe_sprites.txt", ID_TEX_AXE);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\Axe\\Axe_ani.txt", this);
	state = WEPOND_STATE_UNACTIVE;
	this->owner = owner;
	isfinish = true;
}


Axe::~Axe()
{
}

void Axe::UpdatePositionRelateToObject(DWORD dt)
{
	float x1, y1, x2, y2;
	D3DXVECTOR2 newposition;
	owner->GetBoundingBox(x1, y1, x2, y2);
	level = owner->getlevel();
	nx = owner->GetDirect();
	newposition = { x1,y1 + 5 };
	this->SetPosition(newposition.x, newposition.y);
}

void Axe::StartAttack()
{
	if (!isfinish)
		return;
	isfinish = false;
	UpdatePositionRelateToObject(dt);
	state = WEPOND_STATE_ACTIVE;
	vx = THROWINGAXE_SPEED_X * nx;
	vy = -THROWINGAXE_SPEED_Y;
	Sound::getInstance()->play("Axe", false, 1);
}

void Axe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	CGameObject::Update(dt);
	if (!Camera::getInstance()->checkInCamera(x, y, x + AXE_BBOX_WIDTH, y + AXE_BBOX_HEIGHT))
	{
		isfinish = true;
	} 
	if (isfinish)
	{
		state = WEPOND_STATE_UNACTIVE;
		return;
	}
	vy += THROWINGAXE_GRAVITY * dt;
	
	y += dy;
	x += dx;

	DebugOut(L"state axe :%d --orginal y :%d --y:%d \n", state,(int)OrginalY,(int)y);
}

void Axe::reset()
{
	state = WEPOND_STATE_UNACTIVE;
	isfinish = true;
}

void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == WEPOND_STATE_ACTIVE)
	{
		left = x;
		top = y;

		right = left + AXE_BBOX_WIDTH;
		bottom = top + AXE_BBOX_HEIGHT;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Axe::Render()
{
	if (state == WEPOND_STATE_ACTIVE)
	{
		animations[0]->Render(x, y, 255, nx);//
		RenderBoundingBox();
	}
}
