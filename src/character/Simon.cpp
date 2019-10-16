#include "../character/Simon.h"
#include"../sample/Goomba.h"
#include<fstream>
#include <vector>
#include <string>
#include"../map/CBratizer.h"
Simon::Simon(double scalerate)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\player_sprites.txt", ID_TEX_SIMON);
	string source[] = {
	"content\\characters\\player\\player_ani\\idle.txt",
	"content\\characters\\player\\player_ani\\attack.txt",
	"content\\characters\\player\\player_ani\\walk.txt",
	"content\\characters\\player\\player_ani\\goup.txt",
	"content\\characters\\player\\player_ani\\godown.txt",
	"content\\characters\\player\\player_ani\\jump.txt",
	"content\\characters\\player\\player_ani\\sitattack.txt",
	"content\\characters\\player\\player_ani\\sit.txt" };
	LoadResourceHelper::Loadanimationfromfile(source, 8, this);
	this->scale_rate = scalerate;
	untouchable = 0;
	attacking = false;
	level = 1;
	sword_turn = 0;
	onstate = false;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CGameObject::Update(dt);
	if (x < 10)
		x = 10;
	
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


	// No collision occured, proceed normally
	if (GetTickCount() - jumpplus_start > SIMON_ATTACK_TIME)
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
			else
				if (dynamic_cast<Whip_PowerUp*>(object) && object->state == ITEM_STATE_ACTIVE && CheckOverLap(object))
				{
					if (GetTickCount() - overlap_time > SIMON_ATTACK_TIME + 150)
					{
						Whip_PowerUp *lh = dynamic_cast<Whip_PowerUp *>(object);
						lh->SetState(ITEM_STATE_UNACTIVE);
						lh->SetPosition(0 - WHIP_POWER_UP_BBOX_WIDTH, 0);
						this->Upgrate();
					}
				}
				else
					if (dynamic_cast<SwordItem*>(object) && object->state == ITEM_STATE_ACTIVE && CheckOverLap(object))
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
				x += min_tx * dx + nx * 0.5f;		// nx*0.5f : need to push out a bit to avoid overlapping next frame
				y += min_ty * dy + ny * 0.5f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
				onstate = true;
			}
			if (dynamic_cast<Large_heart *>(e->obj))
			{
				if ((e->obj)->GetState() == ITEM_STATE_ACTIVE)
				{
					Large_heart *lh = dynamic_cast<Large_heart *>(e->obj);

					lh->SetState(ITEM_STATE_UNACTIVE);
					lh->SetPosition(0 - LARGE_HEART_BBOX_WIDTH, 0);
					this->sword_turn += 5;
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
	this->Render(1);
}

void Simon::Render(double Scale_rate)
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

	int alpha = 255;
	if (untouchable) alpha = 128;
	if (attacking) {
		ani = SIMON_ANI_ATTACK;
	}
	animations[ani]->Render(x, y, alpha, nx*Scale_rate, Scale_rate);

	RenderBoundingBox();
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
	if (!attacking) {
		attacking = true; attack_start = GetTickCount();
		overlap_time = GetTickCount();
		temp_nx = nx;
	}
}

void Simon::StartmonoJump()
{
	if (!jumping) {
		jumping = true; jump_start = GetTickCount();
		onstate = false;
	}
}

void Simon::StartplexJump()
{
	if (!jumping) {
		jumping = true; jumpplus_start = GetTickCount();
		temp_nx = nx;
		onstate = false;
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
//chua sua
void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	right = x + SIMON_BIG_BBOX_WIDTH * scale_rate;
	bottom = y + SIMON_BIG_BBOX_HEIGHT * scale_rate;


}
