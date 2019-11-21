#include "Sword.h"
#include "../sample/Const_Value.h"
#include <vector>


Sword::Sword()
{
}

Sword::Sword(CGameObject * owner)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\Sword\\Sword_sprites.txt", ID_TEX_SWORD);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\Sword\\Sword_ani.txt", this);
	state = WEPOND_STATE_UNACTIVE;
	this->owner = owner;
	waiting = false;
}

CGameObject * Sword::GetOwner()
{
	return owner;
}

void Sword::UpdatePositionRelateToObject(DWORD dt)
{
	float x1, y1, x2, y2;
	D3DXVECTOR2 newposition;
	owner->GetBoundingBox(x1, y1, x2, y2);
	level = owner->getlevel();
	nx = owner->GetDirect();
	//right
	//simon.nx == 1
	if (owner->GetDirect() == 1)
	{
		newposition = { x2 + 5,y1 + 16 };
	}
	else //Left
	{
		newposition = { x1 - SWORD_BBOX_WIDTH - 5,y1 + 16 };
	}

	this->SetPosition(newposition.x, newposition.y);
}

void Sword::StartAttack()
{
	if (state != WEPOND_STATE_ACTIVE && !attacking && dynamic_cast<Simon*>(owner)->isattacking())
	{
		//state = SWORD_STATE_ACTIVE;
		attacking = true;
		waiting = true;
		attack_start = GetTickCount();
		UpdatePositionRelateToObject(dt);
	}
}

void Sword::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == WEPOND_STATE_ACTIVE || waiting)
	{
		x += vx;
		//waiting time : 200 --> attack time = 200->600
		if (GetTickCount() - attack_start > SIMON_ATTACK_TIME + 200)
		{
			attacking = false;
			attack_start = 0;
			state = WEPOND_STATE_UNACTIVE;
			waiting = false;
			DebugOut(L"ketthuc \n");
		}
		else
		{
			//start transit sword
			if (GetTickCount() - attack_start > SIMON_ATTACK_TIME - 200)
			{
				waiting = false;
				state = WEPOND_STATE_ACTIVE;
				vx = nx * SWORD_FLY_SPEED;
				DebugOut(L"batdau \n");
			}
			//waiting 200ms before transit
			else
			{
				state = WEPOND_STATE_UNACTIVE;
				vx = 0;
				waiting = true;
				DebugOut(L"cho \n");
			}
		}
	}
	DebugOut(L"state sword :%d \n",state);
}

void Sword::reset()
{
	state = WEPOND_STATE_UNACTIVE;
	attack_start = 0;
	attacking = false;
	waiting = false;
}

void Sword::Render()
{
	DebugOut(L"state sword render :%d \n", state);
	if (state == WEPOND_STATE_ACTIVE)
	{
		animations[0]->Render(x, y, 255, nx);//
		RenderBoundingBox();
	}
}

void Sword::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == WEPOND_STATE_ACTIVE)
	{
		left = x;
		top = y;

		right = left + SWORD_BBOX_WIDTH;
		bottom = top + SWORD_BBOX_HEIGHT;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}
