#include "../character/Simon.h"
#include"../sample/Endpoint.h"
#include<fstream>
#include <vector>
#include <string>
#include"../item/CBratizer.h"
Simon* Simon::_instance = NULL;
Simon::Simon()
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\player_sprites.txt", ID_TEX_SIMON);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\player_ani\\allani.txt", this);

	level = 1;
	sword_turn = 0;
}

Simon * Simon::getinstance()
{
	if (_instance == NULL) _instance = new Simon();
	return _instance;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);
	if (x < -5)
		x = 0;
	if(!climbing)
	vy += SIMON_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	
	vector<LPCOLLISIONEVENT> coEventsResult;
	
	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
	{
		CalcPotentialCollisions(colliable_objects, coEvents);
	}
#pragma region attack


	if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
	{
		attack_start = 0;
		attacking = false;
	}
	// no moving when attacking
	else
	{
		nx = temp_nx;
		if(onstair)
		dx = 0;
	}

#pragma endregion
#pragma region mono jump


	// fell down
	if (GetTickCount() - jump_start > SIMON_JUMP_TIME)
	{
		jump_start = 0;
		jumping = false;

	}
	else
	{
		//jumping up
		if (GetTickCount() - jump_start < (SIMON_JUMP_TIME))
		{
			//only jump when onstate;
			if (onstair)
			{
				vy = -SIMON_JUMP_SPEED_Y;
				onstair = false;
			}
			else
			{
				vx = 0;
			}
		}
	}

#pragma endregion
#pragma region plex jump


	//jump and has ->
	if (GetTickCount() - jumpplus_start > SIMON_JUMP_TIME)
	{

		jumpplus_start = 0;
		jumping = false;
	}
	else 
	{
		//jumping up
		if (GetTickCount() - jumpplus_start < (SIMON_JUMP_TIME))
		{
			//only jump when onstate;
			if (onstair)
			{
				vy = -SIMON_JUMP_SPEED_Y;
				vx =  temp_nx*SIMON_JUMP_SPEED_X;
				onstair = false;
			}
			else
			{
				nx = temp_nx;
			}
		}
	}

#pragma endregion
#pragma region collect
	if (GetTickCount() - collect_start > SIMON_TIME_COLLECT)
	{
		collecting = false;
		collect_start = 0;
	}
#pragma endregion

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		//onstate = false;
	}
	else
	{
#pragma region check overlap for item
		for (UINT i = 0; i < colliable_objects->size(); i++)
		{
			CGameObject *object = colliable_objects->at(i);
			if (dynamic_cast<Large_heart*>(object) && object->state == ITEM_STATE_ACTIVE && CheckOverLap(object))
			{
				if (GetTickCount() - overlap_time > SIMON_ATTACK_TIME+150)
				{
					Large_heart *lh = dynamic_cast<Large_heart *>(object);
					lh->SetState(ITEM_STATE_UNACTIVE);
					lh->SetPosition(0 - LARGE_HEART_BBOX_WIDTH, 0);
				}
			}
			else if (dynamic_cast<Whip_PowerUp*>(object) && object->state == ITEM_STATE_ACTIVE && CheckOverLap(object))
				{
					if (GetTickCount() - overlap_time > SIMON_ATTACK_TIME + 150)
					{
						Whip_PowerUp *lh = dynamic_cast<Whip_PowerUp *>(object);
						lh->SetState(ITEM_STATE_UNACTIVE);
						lh->SetPosition(0 - WHIP_POWER_UP_BBOX_WIDTH, 0);
						this->StartCollect();
						this->Upgrate();
					}
				}
			else if (dynamic_cast<SwordItem*>(object) && object->state == ITEM_STATE_ACTIVE && CheckOverLap(object))
					{
						if (GetTickCount() - overlap_time > SIMON_ATTACK_TIME + 150)
						{
							SwordItem *lh = dynamic_cast<SwordItem *>(object);
							lh->SetState(ITEM_STATE_UNACTIVE);
							lh->SetPosition(0 - WHIP_POWER_UP_BBOX_WIDTH, 0);
							this->sword_turn += 5;
						}
					}
		}
#pragma endregion

#pragma region check by AABB
		
		
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CInvisibleObject *>(e->obj))
			{
				// block 
				if (dynamic_cast<CInvisibleObject *>(e->obj)->Gettype() == Const_Value::in_obj_type::Brick)
				{
					x += min_tx * dx + nx * 0.1f;		// nx*0.5f : need to push out a bit to avoid overlapping next frame
					y += min_ty * dy + ny * 0.1f;

					if (nx != 0) vx = 0;
					if (ny != 0) vy = 0;
					onstair = true;
				}
				//endmap1
				else if (dynamic_cast<CInvisibleObject *>(e->obj)->Gettype() == Const_Value::in_obj_type::endmap1)
				{
					endmap1 = true;
				}
			}
			else if (dynamic_cast<Large_heart *>(e->obj))
			{
				if ((e->obj)->GetState() == ITEM_STATE_ACTIVE)
				{
					Large_heart *lh = dynamic_cast<Large_heart *>(e->obj);

					lh->SetState(ITEM_STATE_UNACTIVE);
					lh->SetPosition(0 - LARGE_HEART_BBOX_WIDTH, 0);
					//this->them mau
				}
				
			}
			else if (dynamic_cast<Whip_PowerUp *>(e->obj))
			{
				if ((e->obj)->GetState() == ITEM_STATE_ACTIVE)
				{
					Whip_PowerUp *wp = dynamic_cast<Whip_PowerUp *>(e->obj);

					wp->SetState(ITEM_STATE_UNACTIVE);
					wp->SetPosition(0 - WHIP_POWER_UP_BBOX_WIDTH, 0);
					this->StartCollect();
					this->Upgrate();
				}
				
			}
			else if (dynamic_cast<SwordItem *>(e->obj))
			{
				if ((e->obj)->GetState() == ITEM_STATE_ACTIVE)
				{
					SwordItem *si = dynamic_cast<SwordItem *>(e->obj);

					si->SetState(ITEM_STATE_UNACTIVE);
					si->SetPosition(0 - WHIP_POWER_UP_BBOX_WIDTH, 0);
					this->sword_turn += 5;
				}

			}
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

#pragma endregion
}

void Simon::Render()
{
	int ani;

	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (vy < 0)
	{

		ani = SIMON_ANI_JUMP;
	}
	else
	{
		if (vx == 0)
		{
			if (state == SIMON_STATE_ATTACK)
			{
				ani = SIMON_ANI_ATTACK;
			}
			else
				ani = SIMON_ANI_IDLE;
		}
		else
			ani = SIMON_ANI_WALKING;
	}
	if (attacking) {
		ani = SIMON_ANI_ATTACK;
	}
	/*if (jumping)
		ani = SIMON_ANI_JUMP;*/
	if (state == SIMON_STATE_SIT)
		ani = SIMON_ANI_SIT;
	if (collecting)
		ani = SIMON_ANI_COLLECT;
	if (state == SIMON_STATE_GODOWN)
		ani = SIMON_ANI_GODOWN;
	if (state == SIMON_STATE_GOUP)
		ani = SIMON_ANI_GOUP;

	animations[ani]->Render(x, y, 255, nx);
	RenderBoundingBox();
}

void Simon::setswordturndesc()
{
	if (sword_turn >= 1) sword_turn--; else sword_turn = 0;
}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	default:
		vx = 0;
	}
}

void Simon::StartAttack()
{
	if (!attacking && !collecting) {
		attacking = true;
		attack_start = GetTickCount();
		
		animations[SIMON_ANI_ATTACK]->reset();
		overlap_time = GetTickCount();
		temp_nx = nx;
	}
}

void Simon::StartmonoJump()
{
	if (!jumping && !collecting) {
		jumping = true; jump_start = GetTickCount();
		onstair = false;
	}
}

void Simon::StartplexJump()
{
	if (!jumping && !collecting) {
		jumping = true; jumpplus_start = GetTickCount();
		temp_nx = nx;
		onstair = false;
	}
	
}

void Simon::StartCollect()
{
	if (!collecting) {
		state = SIMON_STATE_COLLECT;
		collecting = true; 
		collect_start = GetTickCount();
	}
}


void Simon::startclimbdown()
{
	if (canclimbdown)
	{
		climbing = true;
		state = SIMON_STATE_GODOWN;
		x += dx;
		y += 1.0f;
	}
}
void Simon::startclimbup()
{
	if (canclimbup)
	{
		climbing = true;
		state = SIMON_STATE_GOUP;
		x += dx;
		y -= 1.0f;
	}
}

void Simon::Upgrate()
{
	if (level < SIMON_MAX_LEVEL)
		level++;
}


int Simon::GetDirect()
{
	return nx;
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	
	left = x+(SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH)/2;
	top = y;
	right = left + SIMON_SMALL_BBOX_WIDTH ;
	bottom = top + SIMON_SMALL_BBOX_HEIGHT;


}
