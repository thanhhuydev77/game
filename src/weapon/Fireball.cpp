#include "Fireball.h"



Fireball::Fireball(float x, float y, int direct)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\Fireball\\Fireball_sprite.txt", ID_TEX_FIREBALL);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\Fireball\\Fireball_ani.txt", this);
	this->x = x;
	this->y = y;
	this->nx = direct;
	vx = nx*FIREBALL_SPEED;
}


Fireball::~Fireball()
{
}

void Fireball::restart(float x, float y, int direct)
{
	this->x = x;
	this->y = y;
	this->nx = direct;
	vx = nx * FIREBALL_SPEED;
	isfinish = false;
}

void Fireball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (isfinish)
		return;
	float t, l, r, b;
	GetBoundingBox(l, t, r, b);
	RECT check;
	check.left = l;
	check.top = t;
	check.right = r;
	check.bottom = b;
	// still in camera
	if (Camera::getInstance()->checkInCamera(check))
	{	x += dx;
		y += dy;
	}
	else
	{
		isfinish = true;
	}
}

void Fireball::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void Fireball::Render()
{
	if(!isfinish)
	animations[0]->Render(x, y, 255,nx);
}
