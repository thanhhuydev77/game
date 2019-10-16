#include "Whip.h"
#include "../sample/Const_Value.h"
#include <vector>

int Whip::GetLevel()
{
	return level;
}

CGameObject * Whip::GetOwner()
{
	return owner;
}

void Whip::UpdatePositionRelateToObject(DWORD dt)
{
	float x1, y1, x2, y2;
	D3DXVECTOR2 newposition;
	owner->GetBoundingBox(x1, y1, x2, y2);
	level = owner->getlevel();
	nx = owner->GetDirect();
	int frame = animations[level - 1]->GetCurrentFrame();
	int t1 = animations[level - 1]->GetFrame(0)->GetTime();
	int t2 = animations[level - 1]->GetFrame(1)->GetTime() + t1;
	int t3 = animations[level - 1]->GetFrame(2)->GetTime() + t2;
	//right
	//simon.nx == 1
	if (owner->GetDirect() == 1)
	{
		switch (frame)
		{
		case 0:
			if (GetTickCount() - attack_start <= t1)
				newposition = { x1 - WHIP_F1_BBOX_WIDTH + 10, y1 + 14 };

			break;
		case 1:
			if (GetTickCount() - attack_start < t2)
				newposition = { x1 - WHIP_F2_BBOX_WIDTH + 10, y1 + 9 };

			break;
		case 2:
			if (GetTickCount() - attack_start <= t3)
				newposition = { x2 + 4 ,y1 + 30 - WHIP_F3_BBOX_HEIGHT };

			break;
		}
	}
	else // Facing::Left
	{
		switch (animations[level - 1]->GetCurrentFrame())
		{

		case 0:
			if (GetTickCount() - attack_start <= t1)
				newposition = { x2 + 13, y1 + 14 };
			break;
		case 1:
			if (GetTickCount() - attack_start <= t2)
				newposition = { x2 + 13, y1 + 14 };
			break;
		case 2:
			if (GetTickCount() - attack_start <= t3)
				if (level != 3)
					newposition = { x1 - WHIP_F3_BBOX_WIDTH + 10 , y1 + 29 - WHIP_F3_BBOX_HEIGHT };
				else
					newposition = { x1 - WHIP_F3_HLV_BBOX_WIDTH + 12 , y1 + 33 - WHIP_F3_BBOX_HEIGHT };
			break;

		}
	}

	this->SetPosition(newposition.x, newposition.y);
}

void Whip::Upgrade()
{
	if (level + 1 <= WHIP_MAX_LEVEL)
		level++;
}

void Whip::StartAttack()
{
	if (state != WHIP_STATE_ACTIVE)
	{
		state = WHIP_STATE_ACTIVE;
		attack_start = GetTickCount();
		animations[level - 1]->reset();

	}
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	UpdatePositionRelateToObject(dt);
	if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
	{
		attack_start = 0;
		state = WHIP_STATE_UNACTIVE;
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

void Whip::Render()
{
	Render(1.0f);
}

Whip::Whip()
{
}

Whip::Whip(double scalerate, CGameObject * owner)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\whip\\whip_sprites.txt", ID_TEX_WHIP);
	string source[] = {
		"content\\characters\\player\\whip\\whip_ani_lv1.txt",
		"content\\characters\\player\\whip\\whip_ani_lv2.txt",
		"content\\characters\\player\\whip\\whip_ani_lv3.txt"
	};
	LoadResourceHelper::Loadanimationfromfile(source, 3, this);
	level = 3;
	state = WHIP_STATE_UNACTIVE;
	this->owner = owner;
}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	int frame = animations[level - 1]->GetCurrentFrame();
	left = x;
	top = y;
	switch (frame)
	{
	case 0:
	case 1:
		right = x;
		bottom = y;
		break;
	case 2:
		if (level == 1)
		{
			right = x + WHIP_F3_BBOX_WIDTH;
			bottom = y + WHIP_F3_BBOX_HEIGHT;
		}
		else if (level == 2)
		{
			right = x + WHIP_F3_BBOX_WIDTH;
			bottom = y + WHIP_F3_BBOX_HEIGHT;
		}
		//lv3 
		else
		{
			right = x + WHIP_F3_HLV_BBOX_WIDTH;
			bottom = y + WHIP_F3_BBOX_HEIGHT;
		}
	default:
		break;
	}

}

void Whip::Render(double scale_rate)
{
	if (state == WHIP_STATE_ACTIVE)
	{
		//level begin at 1 and ani begin at 0
		animations[level - 1]->Render(x, y, 255, nx*scale_rate, scale_rate);//
		RenderBoundingBox();
	}

}
