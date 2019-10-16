#include "Sword.h"
#include "Const_Value.h"
#include <vector>


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
		newposition = { x2,y1 + 5 };
	}
	else //Left
	{
		newposition = { x1 - SWORD_BBOX_WIDTH,y1 + 5 };
	}

	this->SetPosition(newposition.x, newposition.y);
}

void Sword::StartAttack()
{
	if (state != SWORD_STATE_ACTIVE)
	{
		
		state = SWORD_STATE_ACTIVE;
		attack_start = GetTickCount();
		UpdatePositionRelateToObject(dt);
	}
}

void Sword::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (state == SWORD_STATE_ACTIVE)
	{

		x += vx;
		if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
		{
			attack_start = 0;
			state = SWORD_STATE_UNACTIVE;
		}
		else
		{
			vx = nx * SWORD_FLY_SPEED;
		}
		vector<LPGAMEOBJECT> bra;
		vector<LPGAMEOBJECT> item;
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CBratizer *>(coObjects->at(i)))
				bra.push_back(coObjects->at(i));
			else
				item.push_back(coObjects->at(i));
		}
		for (UINT i = 0; i < bra.size(); i++)
		{
			CBratizer *bratizer = dynamic_cast<CBratizer *>(bra[i]);
			if (CheckOverLap(bratizer))
			{
				bratizer->SetState(BRATIZER_STATE_UNACTIVE);
				float x, y;
				if (dynamic_cast<Large_heart *>(item[i]))
					item[i]->SetState(ITEM_STATE_ACTIVE);
				else
					item[i]->SetState(ITEM_STATE_ACTIVE);
			}
		}

	}
}

void Sword::Render()
{
	Render(1.0f);
}

Sword::Sword()
{
}

Sword::Sword(double scalerate, CGameObject * owner)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\Sword\\Sword_sprites.txt", ID_TEX_SWORD);
	string source[] = {
		"content\\characters\\player\\Sword\\Sword_ani.txt"
	};
	LoadResourceHelper::Loadanimationfromfile(source, 1, this);
	state = SWORD_STATE_UNACTIVE;
	this->owner = owner;
	
}

void Sword::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

	left = x;
	top = y;
	right = x + SWORD_BBOX_WIDTH;
	bottom = y + SWORD_BBOX_HEIGHT;


}

void Sword::Render(double scale_rate)
{
	if (state == SWORD_STATE_ACTIVE)
	{
		animations[0]->Render(x, y, 255, nx*scale_rate, scale_rate);//
		RenderBoundingBox();
	}

}
