#include "Bat.h"

Bat::Bat(float X, float Y, int Direction)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\enemies\\vampirebat_sprite.txt", ID_TEX_VAMPIREBAT);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\enemies\\vampirebat_ani.txt", this);

	LoadResourceHelper::Loadspritefromfile("content\\effect\\flame_sprite.txt", ID_TEX_FLAME);
	LoadResourceHelper::Loadanimationfromfile("content\\effect\\flame_ani.txt", this);
	this->x = X;
	this->y = Y;
	this->yBackup = y;
	this->nx = Direction;
	this->Health = 1;
	state = ENEMY_STATE_LIVE;
	vy = BAT_SPEED_Y;
	vx = BAT_SPEED_X * nx;
}

Bat::~Bat()
{
}
//
void Bat::start_disappear()
{
	disappearing = true;
	disappear_start = GetTickCount();
}
//
void Bat::takedamage()
{
	state = ENEMY_STATE_DIE;
	start_disappear();
	vx = 0;
	vy = 0;
}

void Bat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (Health <= 0)
		return;
	CGameObject::Update(dt);
	if (y - yBackup >= DeltaY)
	{
		vy = -BAT_SPEED_Y;
	}
	else
		if (y - yBackup <= -DeltaY)
		{
			vy = BAT_SPEED_Y;
		}
	
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
	y += dy;
	x += dx;
	/*if (x <= 3034 || x >= 4092)
	{
		Health = 0;
	}*/
}

void Bat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + BAT_BBOX_WIDTH;
	bottom = top + BAT_BBOX_HEIGHT;
}

void Bat::Render()
{
	if (Health <= 0)
		return;
	if (!disappearing)
		animations[1]->Render(x, y, 255);
	else
		animations[2]->Render(x, y, 255);
}
