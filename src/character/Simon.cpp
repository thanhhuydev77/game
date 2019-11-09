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
	if (!climbing)
	{
		vy += SIMON_GRAVITY * dt;
	}
	else {
		vy = 0;
	}

	if (autoclimbing || autowalking)
	{
		//start autoclimb when not auto walk
		//1 is walking first,2 is climb first
		if (autowalking && dofirst == 1)
		{

			//walking to left
			if (temp_nx == -1 && x - targetX > 0)
			{
				SetState(SIMON_STATE_WALKING_LEFT);
				x += dt * vx;
			}
			//walking to right
			else if (temp_nx == 1 && x - targetX < 0)
			{
				SetState(SIMON_STATE_WALKING_RIGHT);
				x += dt * vx;
			}
			//end of auto
			else
			{
				orginX = x;
				orginY = y;
				autowalking = false;
				nx = last_nx;
				dofirst = 2;
				climbing = false;
				/*if (canclimbup)
					x += nx*15;
				else if(canclimbdown)
					x -= nx*15;*/
			}
		}
		else if (autoclimbing && dofirst == 2)
		{
			//climb up
			
			if (y + SIMON_BIG_BBOX_HEIGHT > targetY && temp_ny == -1)
			{
				startclimbup();

			}
			//climb down
			else if (y + SIMON_BIG_BBOX_HEIGHT < targetY && temp_ny == 1)
			{
				startclimbdown();
			}
			else
			{
				autoclimbing = false;
				dofirst = 1;
				//nx = temp_nx;
			}
		}

	}
	else if (!climbing)
	{
		
		{
			vector<LPCOLLISIONEVENT> coEvents;

			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();
			// turn off collision when die 
			if (state != SIMON_STATE_DIE)
			{
				CalcPotentialCollisions(colliable_objects, coEvents);
			}


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
						if (GetTickCount() - overlap_time > SIMON_ATTACK_TIME + 150)
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
							onGround = true;
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
		}

#pragma endregion
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
		if (onGround)
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
			if (onGround)
			{
				vy = -SIMON_JUMP_SPEED_Y;
				onGround = false;
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
			if (onGround)
			{
				vy = -SIMON_JUMP_SPEED_Y;
				vx = temp_nx * SIMON_JUMP_SPEED_X;
				onGround = false;
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

	
	/*DebugOut(L"autowalking: %d--", autowalking);
	DebugOut(L"autoclimbing: %d--", autoclimbing);
	DebugOut(L"temp ny: %d\n", temp_ny);
	DebugOut(L"temp nx: %d\n", temp_nx);*/
	DebugOut(L"tam x = %d . tam y = %d . x = %d . y=%d \n", (int)tempx, (int)tempy, (int)x, (int)y);
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
			if (state == SIMON_STATE_ATTACK )
			{
				ani = SIMON_ANI_ATTACK;
			}
			
			else if (state == SIMON_STATE_STANDING_ONSTAIR &&!attacking)
			{
				if (nx == climb_direct)
					animations[SIMON_ANI_GOUP]->GetFrame(1)->GetSprite()->Draw(x, y, 255, nx);
				else
					animations[SIMON_ANI_GODOWN]->GetFrame(1)->GetSprite()->Draw(x, y, 255, nx);
			}
			else

				ani = SIMON_ANI_IDLE;
		}
		else
			ani = SIMON_ANI_WALKING;
	}
	if (attacking) {
		if (climbing && nx == climb_direct)
			ani = SIMON_ANI_GOUP_ATTACK;
		else if(climbing && nx != climb_direct)
			ani = SIMON_ANI_GODOWN_ATTACK;
		else
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
	/*if (state == SIMON_STATE_GODOWN_ATTACK)
		ani = SIMON_ANI_GODOWN_ATTACK;
	if (state == SIMON_STATE_GOUP_ATTACK)
		ani = SIMON_ANI_GOUP_ATTACK;*/
	if (state == SIMON_STATE_STANDING_ONSTAIR &&!attacking)
	{
		 if (nx == climb_direct)
			animations[SIMON_ANI_GOUP]->GetFrame(1)->GetSprite()->Draw(x, y, 255, nx);
		else
			animations[SIMON_ANI_GODOWN]->GetFrame(1)->GetSprite()->Draw(x, y, 255, nx);
	}
	else
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

void Simon::setcanclimb(bool icanclimb, bool up)
{
	if (up)
		canclimbup = icanclimb;
	else
		canclimbdown = icanclimb;
}

void Simon::StartAttack()
{
	if (!attacking && !collecting) {
		attacking = true;
		attack_start = GetTickCount();

		animations[SIMON_ANI_ATTACK]->reset();
		animations[SIMON_ANI_GOUP_ATTACK]->reset();
		animations[SIMON_ANI_GODOWN_ATTACK]->reset();
		overlap_time = GetTickCount();
		temp_nx = nx;
	}
}

void Simon::StartmonoJump()
{
	if (!jumping && !collecting) {
		jumping = true; jump_start = GetTickCount();
		onGround = false;
	}
}

void Simon::StartplexJump()
{
	if (!jumping && !collecting) {
		jumping = true; jumpplus_start = GetTickCount();
		temp_nx = nx;
		onGround = false;
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

void Simon::startAutowalk(int lastdirect, float targetX)
{
	if (!autoclimbing)
		dofirst = 1;
	// according to current locate to determine nx when walking
	this->targetX = targetX;
	//stair direct is left
	temp_nx = (x > targetX) ? -1 : 1;
	nx = temp_nx;
	climbing = false;
	autowalking = true;
	this->last_nx = lastdirect;
}

void Simon::startAutoClimb(int lastdirect, float targetY)
{
	if (!autowalking)
		dofirst = 2;
	tempx = x;
	tempy = y;
	autoclimbing = true;
	//this->targetX = targetX;
	//temp_ny = (y + SIMON_BIG_BBOX_HEIGHT > targetY) ? -1 : 1;
	this->targetY = targetY;
	climb_direct = lastdirect;
	nx = lastdirect;

	//climb to left
	//this->last_nx = lastdirect;
}

void Simon::startclimbdown()
{
	if (canclimbdown && !attacking)
	{
		climbing = true;
		nx = -climb_direct;
		state = SIMON_STATE_GODOWN;
		x -= climb_direct * 1.0f;
		y += 1.0f;
		/*if ((int)(tempy - y) % 4 == 0)
		{
			x = tempx;
			y = tempy;
		}*/
	}
}

void Simon::startclimbup()
{
	if (canclimbup  && !attacking)
	{
		climbing = true;
		nx = climb_direct;
		state = SIMON_STATE_GOUP;
		x += climb_direct * 1.0f;
		y -= 1.0f;
		/*if ((int)(y - tempy) % 4 == 0)
		{
			x = tempx;
			y = tempy;
		}*/
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

	left = x + (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2;
	top = y;
	right = left + SIMON_SMALL_BBOX_WIDTH;
	bottom = top + SIMON_SMALL_BBOX_HEIGHT;


}
