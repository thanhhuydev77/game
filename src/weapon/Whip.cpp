#include "Whip.h"
#include "../sample/Const_Value.h"
#include <vector>

Whip::Whip()
{
}

Whip::Whip( CGameObject * owner)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\whip\\whip_sprites.txt", ID_TEX_WHIP);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\whip\\whip_ani.txt", this);
	
	level = 0;
	state = WHIP_STATE_UNACTIVE;
	this->owner = owner;
}

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
	unsigned int t1 = animations[0]->GetFrame(0)->GetTime();
	unsigned int t2 = animations[0]->GetFrame(1)->GetTime() + t1;
	unsigned int t3 = animations[0]->GetFrame(2)->GetTime() + t2;

	//level 1,2
	if (level != 3)

	{	//right
	//simon.nx == 1
		if (owner->GetDirect() == 1)
		{
			switch (frame)
			{
			case 0:
				if (GetTickCount() - attack_start <= t1)
					newposition = { x1 - WHIP_F1_BBOX_WIDTH -9  , y1 + 13 };

				break;
			case 1:
				if (GetTickCount() - attack_start < t2)
					newposition = { x1 - WHIP_F2_BBOX_WIDTH -9 , y1 + 13 };

				break;
			case 2:
				if (GetTickCount() - attack_start <= t3)
					newposition = { x2 + 12,y2 - 46 };

				break;
			}
		}
		else // Facing::Left
		{
			switch (animations[level - 1]->GetCurrentFrame())
			{

			case 0:
				if (GetTickCount() - attack_start <= t1)
					newposition = { x2 + 9, y1 + 13 };
				break;
			case 1:
				if (GetTickCount() - attack_start <= t2)
					newposition = { x2 + 9, y1 + 13 };
				break;
			case 2:
				if (GetTickCount() - attack_start <= t3)
					/*if (level != 3)*/
					newposition = { x1 - WHIP_F3_BBOX_WIDTH -11,y2 - 46 };
				/*else
					newposition = { x1 - WHIP_F3_HLV_BBOX_WIDTH + 12 , y1 + 33 - WHIP_F3_BBOX_HEIGHT };*/
				break;

			}
		}
	}
	else //level 3
	{
		{	//right
			//simon.nx == 1
			if (owner->GetDirect() == 1)
			{
				switch (frame)
				{
				case 0:
				case 1:
				case 2:
				case 3:
					if (GetTickCount() - attack_start <= t1)
						newposition = { x1 - WHIP_F1_BBOX_WIDTH - 9  , y1 + 13 };
					break;
				case 4:
				case 5:
				case 6:
				case 7:
					if (GetTickCount() - attack_start < t2)
						newposition = { x1 - WHIP_F2_BBOX_WIDTH - 9 , y1 + 13 };
					break;
				case 8:
				case 9:
				case 10:
				case 11:
					if (GetTickCount() - attack_start <= t3)
						newposition = { x2 + 12,y2 - 46 };
					break;
				}
			}
			else // Facing::Left
			{
				switch (animations[level - 1]->GetCurrentFrame())
				{

				case 0:
				case 1:
				case 2:
				case 3:
					if (GetTickCount() - attack_start <= t1)
						newposition = { x2 + 9, y1 + 13 };
					break;
				case 4:
				case 5:
				case 6:
				case 7:
					if (GetTickCount() - attack_start <= t2)
						newposition = { x2 + 9, y1 + 13 };
					break;
				case 8:
				case 9:
				case 10:
				case 11:
					if (GetTickCount() - attack_start <= t3)
						/*if (level != 3)
							newposition = { x1 - WHIP_F3_BBOX_WIDTH + 10 , y1 + 29 - WHIP_F3_BBOX_HEIGHT };
						else*/
						newposition = { x1 - WHIP_F3_HLV_BBOX_WIDTH - 11,y2 - 46 };
					break;

				}
			}
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
	if (state != WHIP_STATE_ACTIVE && owner->GetState() != SIMON_STATE_COLLECT)
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
			//bratizer->start_disappear();
			bratizer->SetPosition(-BRATIZER_BBOX_WIDTH, 0);
			item[i]->SetState(ITEM_STATE_ACTIVE);
		}
	}

}

void Whip::Render()
{
	if (state == WHIP_STATE_ACTIVE)
	{
		//level begin at 1 and ani begin at 0
		animations[level - 1]->Render(x, y, 255, nx);//
		RenderBoundingBox();
	}

}

void Whip::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

	int frame = animations[level - 1]->GetCurrentFrame();
	left = x;
	top = y;
	if (level != 3)   //level 1,2
		switch (frame)
		{
		case 0:
		{
			right = left + WHIP_F1_BBOX_WIDTH ;
			bottom = top + WHIP_F1_BBOX_HEIGHT;
			break;
		}
		case 1:
		{
			right = left + WHIP_F2_BBOX_WIDTH ;
			bottom = top + WHIP_F2_BBOX_HEIGHT ;
			break;
		}
		case 2:
		{
			right = left + WHIP_F3_BBOX_WIDTH ;
			bottom = top + WHIP_F3_BBOX_HEIGHT ;
			break;
		}
		default:
			right = left;
			bottom = top;
			break;
		}
	else //level 3
		
		switch (frame)
		{

		case 0:
		case 1:
		case 2:
		case 3:
		{
			
			
			right = left + WHIP_F1_BBOX_WIDTH ;
			bottom = top + WHIP_F1_BBOX_HEIGHT ;
			break;
		}
		case 4:
		case 5:
		case 6:
		case 7:
		{
			
			right = left + WHIP_F2_BBOX_WIDTH ;
			bottom = top + WHIP_F2_BBOX_HEIGHT ;
			break;
		}
		case 8:
		case 9:
		case 10:
		case 11:
		{
			right = left + WHIP_F3_HLV_BBOX_WIDTH ;
			bottom = top + WHIP_F3_BBOX_HEIGHT ;
			break;
		}
		default:
			right = left;
			bottom = top;
			break;
		}
}
