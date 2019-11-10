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
	state = SWORD_STATE_UNACTIVE;
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
	if (state != SWORD_STATE_ACTIVE && !attacking && dynamic_cast<Simon*>(owner)->isattacking())
	{
		state = SWORD_STATE_ACTIVE;
		attacking = true;
		waiting = true;
		attack_start = GetTickCount();
		UpdatePositionRelateToObject(dt);
	}
}

void Sword::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == SWORD_STATE_ACTIVE || waiting)
	{

		x += vx;
		//waiting time : 200 --> attack time = 200->600
		if (GetTickCount() - attack_start > SIMON_ATTACK_TIME + 200)
		{
			attacking = false;
			attack_start = 0;
			state = SWORD_STATE_UNACTIVE;
			waiting = false;
		}
		else
		{
			//start transit sword
			if (GetTickCount() - attack_start > SIMON_ATTACK_TIME - 200)
			{
				waiting = false;
				state = SWORD_STATE_ACTIVE;
				vx = nx * SWORD_FLY_SPEED;
			}
			//waiting 200ms before transit
			else
			{
				state = SWORD_STATE_UNACTIVE;
				vx = 0;
				waiting = true;
			}
		}
		vector<LPGAMEOBJECT> bra;
		vector<LPGAMEOBJECT> item;
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<BoundItem *>(coObjects->at(i)))
				bra.push_back(coObjects->at(i));
			else
				item.push_back(coObjects->at(i));
		}
		for (UINT i = 0; i < bra.size(); i++)
		{
			BoundItem *bratizer = dynamic_cast<BoundItem *>(bra[i]);
			if (CheckOverLap(bratizer) && bratizer->GetState() == BRATIZER_STATE_ACTIVE)
			{
				bratizer->SetState(BRATIZER_STATE_UNACTIVE);
				bratizer->SetPosition(-BRATIZER_BBOX_WIDTH, 0);
				this->state = SWORD_STATE_UNACTIVE;
				this->attacking = false;
				if (dynamic_cast<SmallItem *>(item[i]))
					item[i]->SetState(ITEM_STATE_ACTIVE);
				else
					item[i]->SetState(ITEM_STATE_ACTIVE);
			}
		}

	}
}

void Sword::Render()
{
	if (state == SWORD_STATE_ACTIVE)
	{
		animations[0]->Render(x, y, 255, nx);//
		RenderBoundingBox();
	}
}

void Sword::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

	left = x;
	top = y;

	right = left + SWORD_BBOX_WIDTH;
	bottom = top + SWORD_BBOX_HEIGHT;
}
