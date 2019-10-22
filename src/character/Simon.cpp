#include "../character/Simon.h"
#include"../sample/Goomba.h"
#include<fstream>
#include <vector>
#include <string>
#include"../item/CBratizer.h"
Simon::Simon(double scalerate)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\player_sprites.txt", ID_TEX_SIMON);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\player_ani\\allani.txt", this);

	this->scale_rate = scalerate;
	level = 1;
	sword_turn = 0;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);
	if (x < -5)
		x = 0;
	
	vy += SIMON_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(colliable_objects, coEvents);
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
		if(onstate)
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
			if (onstate)
			{
				vy = -SIMON_JUMP_SPEED_Y;
				onstate = false;
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
			if (onstate)
			{
				vy = -SIMON_JUMP_SPEED_Y;
				vx =  temp_nx*SIMON_JUMP_SPEED_X;
				onstate = false;
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
			if (dynamic_cast<CBrick *>(e->obj))
			{
				// block 
				x += min_tx * dx + nx * 0.1f;		// nx*0.5f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.1f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				onstate = true;
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

	animations[ani]->Render(x, y, 255, nx*scale_rate);
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
		onstate = false;
	}
}

void Simon::StartplexJump()
{
	if (!jumping && !collecting) {
		jumping = true; jumpplus_start = GetTickCount();
		temp_nx = nx;
		onstate = false;
	}
	
}

void Simon::StartCollect()
{
	if (!collecting) {
		collecting = true; collect_start = GetTickCount();
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
	
	x_p = (SIMON_BIG_BBOX_WIDTH -  SIMON_SMALL_BBOX_WIDTH  * scale_rate)/2;
	y_p = (SIMON_BIG_BBOX_HEIGHT - SIMON_SMALL_BBOX_HEIGHT * scale_rate)/2;
	left = x+x_p;
	top = y+y_p;
	right = left + SIMON_SMALL_BBOX_WIDTH * scale_rate ;
	bottom = top + SIMON_SMALL_BBOX_HEIGHT * scale_rate;


}
