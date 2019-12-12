#include "../character/Simon.h"
#include"../sample/Endpoint.h"
#include<fstream>
#include <vector>
#include <string>
#include"../item/BoundItem.h"
Simon* Simon::_instance = NULL;
void Simon::takedamage(int damage, int direct)
{
	Health -= damage;
	hurting = true;
	if (climbing)
		StartUntouchable();
	else
	{
		StartHurting(direct);
		StartUntouchable();
	}
	if (Health <= 0)
	{
		Sound::getInstance()->play("Life_Lost", false,2);
		timeDie = GetTickCount();
	}
}

Simon::Simon(vector<LPGAMEOBJECT> *listeffect)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\player_sprites.txt", ID_TEX_SIMON);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\player_ani\\allani.txt", this);
	Health = SIMON_DEFAULT_HEALTH;
	level = SIMON_DEFAULT_LEVEL;
	NumofLife = SIMON_DEFAULT_TIME_COMEBACK;
	this->listeffect = listeffect;
}

Simon * Simon::getinstance(vector<LPGAMEOBJECT> *listeffect)
{
	if (_instance == NULL) _instance = new Simon(listeffect);
	return _instance;
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	
	CGameObject::Update(dt);
	if (x<Camera::getInstance()->Getx())
	{
		x += 1.0f;
		return;
	}
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount() - startinvisible > SIMON_INVISIBLE_TIME)
	{
		startinvisible = 0;
		invisible = false;
		//Sound::getInstance()->play("InvisibilityPotion_End", false, 1);
	}
	if (GetTickCount() - pause_start > SIMON_CLOCKUP_TIME)
	{
		pausing = false;

	}
	if (collectingcross)
	{
		if (GetTickCount() - timecross > SIMON_CROSSING_TIME)
		{
			collectingcross = false;
			destroyall = false;
			timecross = 0;
		}
		else
		{
			if(dt%2 == 0)
			destroyall = !destroyall;
			DebugOut(L"whiting\n");
		}
	}
#pragma region hurting
	if (GetTickCount() - hurt_start > SIMON_JUMP_TIME)
	{
		hurt_start = 0;
		hurting = false;
	}
	else
	{
		//jumping up
		state = temp_state;
		attacking = false;
		if (GetTickCount() - hurt_start < (SIMON_JUMP_TIME / 2))
		{
			vx = -temp_nx * SIMON_HURT_SPEED_X;
			temp_vx = vx;
			dx = temp_vx * dt;
			if (onGround)
			{
				vy = -SIMON_HURT_SPEED_Y;
				onGround = false;
				dx = 0;
			}
			else
			{
				nx = temp_nx;
			}
		}
		else if (GetTickCount() - hurt_start >= (SIMON_JUMP_TIME / 2))
		{
			nx = temp_nx;
			dx = temp_vx * dt;
			if (onGround)
			{
				resetToDefault();
			}
		}
	}
	if (y > DEADSTAGE)
	{
		if (NumofLife >= 1)
		{
			comeback();
			NumofLife--;
		}
	}
	if (GetTickCount() - timeDie > DEADSTAGE && timeDie != 0)
	{
		if (NumofLife >= 1)
		{
			comeback();
			NumofLife--;
		}
		else
		{
			isGameOver = true;
		}
	}
	if (Health <= 0)
	{
		state = SIMON_STATE_DIE;
		
		return;
		
	}
#pragma endregion

	if (!climbing)
	{
		vy += SIMON_GRAVITY * dt;
	}
	else {
		vy = 0;
	}
	vector<LPGAMEOBJECT> list_enemy;
	list_enemy.clear();
	for (UINT i = 0; i < colliable_objects->size(); i++)
		if (dynamic_cast<Ghost*>(colliable_objects->at(i)) || dynamic_cast<Bat*>(colliable_objects->at(i)) || dynamic_cast<Panther*>(colliable_objects->at(i)) || dynamic_cast<Fishmen*>(colliable_objects->at(i)) || dynamic_cast<Fireball*>(colliable_objects->at(i))|| dynamic_cast<Boss*>(colliable_objects->at(i)))
			list_enemy.push_back(colliable_objects->at(i));



	if (autoclimbing || autowalking)
	{
		//start autoclimb when not auto walk
		//1 is walking first,2 is climb first
		if (autowalking && dofirst == 1 && !Camera::getInstance()->isautogo())
		{

			//walking to left
			if (temp_nx == -1 && x - targetX > 0)
			{
				SetState(SIMON_STATE_WALKING_LEFT);
				x += nx*speedauto;
				
			}
			//walking to right
			else if (temp_nx == 1 && x - targetX < 0)
			{
				SetState(SIMON_STATE_WALKING_RIGHT);
				x +=  nx*speedauto;
				
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
#pragma region mono jump


		// fell down
		if (GetTickCount() - jump_start > SIMON_JUMP_TIME)
		{
			jump_start = 0;
			jumpingmono = false;
			//onGround = true;
		}
		else
		{
			//jumping up
			if (GetTickCount() - jump_start < (SIMON_JUMP_TIME / 2))
			{
				state = temp_state;
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
			else {
				state = temp_state;
			}
		}

#pragma endregion
#pragma region plex jump


		//jump and has ->
		if (GetTickCount() - jumpplus_start > SIMON_JUMP_TIME)
		{

			jumpplus_start = 0;
			jumpingplex = false;
			//onGround = true;
		}
		else
		{
			//jumping up
			state = temp_state;
			if (GetTickCount() - jumpplus_start < (SIMON_JUMP_TIME / 2))
			{
				//only jump when onstate;

				//DebugOut(L"time up: %d--", GetTickCount() - jumpplus_start);
				vx = temp_nx * SIMON_JUMP_SPEED_X;
				temp_vx = vx;
				dx = temp_vx * dt;
				if (onGround)
				{
					vy = -SIMON_JUMP_SPEED_Y;
					onGround = false;
					dx = 0;
				}
				else
				{
					nx = temp_nx;
				}
			}
			else if (GetTickCount() - jumpplus_start >= (SIMON_JUMP_TIME / 2))
			{
				nx = temp_nx;
				dx = temp_vx * dt;
				if (onGround)
				{
					resetToDefault();
					//dx = 0;
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
		{
			vector<LPCOLLISIONEVENT> coEvents;

			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();
			// turn off collision when die 

			CalcPotentialCollisions(colliable_objects, coEvents);



			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
				//onstate = false;
				onGround = false;
			}
			else
			{
#pragma region check overlap for item
				for (UINT i = 0; i < colliable_objects->size(); i++)
				{
					CGameObject *object = colliable_objects->at(i);
					if (dynamic_cast<SmallItem*>(object) && object->state == ITEM_STATE_ACTIVE && CheckOverLap(object))
					{
						if (GetTickCount() - overlap_time > SIMON_ATTACK_TIME + 150)
						{
							//SmallItem *lh = dynamic_cast<SmallItem *>(object);
							collisionwithSmallItem(object);
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
						switch (dynamic_cast<CInvisibleObject *>(e->obj)->Gettype())
						{
						case Const_Value::in_obj_type::Brick:
							if (hurting)
							{
								x += -this->nx * vx;

								//y += min_ty * dy + ny * 0.4f;
							}
							else
							{
								x += min_tx * dx + nx * 0.4f;		// nx*0.5f : need to push out a bit to avoid overlapping next frame
								y += min_ty * dy + ny * 0.4f;
							}
							if (nx != 0)
							{
								resetToDefault();
								vx = 0;
							}
							if (ny != 0)
							{
								if (ny > 0)
								{
									vy = 0;
								}
								else
								{
									vy = 0;
									onGround = true;
								}
							}

							break;
						case Const_Value::in_obj_type::endmap1:
							endmap1 = true;
							break;
						default:
							break;
						}
					}
					else if (dynamic_cast<SmallItem *>(e->obj))
					{
						if ((e->obj)->GetState() == ITEM_STATE_ACTIVE)
						{
							//SmallItem *lh = dynamic_cast<SmallItem *>(e->obj);
							collisionwithSmallItem(e->obj);
						}
					}
					else if (dynamic_cast<BoundItem *>(e->obj))
					{
						x += min_tx * dx + nx * 0.1f;		// nx*0.5f : need to push out a bit to avoid overlapping next frame
						y += min_ty * dy + ny * 0.1f;

						if (nx != 0)
						{
							resetToDefault();
							vx = 0;
						}
						if (ny != 0)
						{
							if (ny > 0)
								vy = 0;
							else
							{
								vy = 0;
								onGround = true;
							}
						}

					}
					//only allow go to right when meet door
					else if (dynamic_cast<StaticObject *>(e->obj) && nx == -1 &&!isJumping())
					{
						startAutowalk(-nx, x + 120);
						dynamic_cast<StaticObject *>(e->obj)->start_open();
						Camera::getInstance()->nextarea();
						x += min_tx * dx + nx * 0.1f;		// nx*0.5f : need to push out a bit to avoid overlapping next frame
						y += min_ty * dy + ny * 0.1f;

						if (nx != 0)
						{
							resetToDefault();
							vx = 0;
						}
						if (ny != 0)
						{
							if (ny > 0)
								vy = 0;
							else
							{
								vy = 0;
								onGround = true;
							}
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
		state = temp_state;
		if (onGround)
			dx = 0;
		jumpingmono = jumpingplex = attacwhenjump;
	}

#pragma endregion

	collisionwithenemy(&list_enemy);
	//DebugOut(L"health :%d \n", Health);
}

void Simon::Render()
{
	int ani;
	int alpha = 255;
	if (untouchable == 1)
		alpha = 170;
	if (invisible)
		alpha = 40;
	if (vy < 0)
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

			else if (state == SIMON_STATE_STANDING_ONSTAIR && !attacking)
			{
				if (nx == climb_direct)
					animations[SIMON_ANI_GOUP]->GetFrame(1)->GetSprite()->Draw(x, y, alpha, nx);
				else
					animations[SIMON_ANI_GODOWN]->GetFrame(1)->GetSprite()->Draw(x, y, alpha, nx);
			}
			else

				ani = SIMON_ANI_IDLE;
		}
		else
			ani = SIMON_ANI_WALKING;
	}

	if (jumpingmono || jumpingplex)
	{
		if (attacking)
			ani = SIMON_ANI_SIT_ATTACK;
		else
			ani = SIMON_ANI_SIT;
	}
	if (attacking)
	{
		if (jumpingmono || jumpingplex || state == SIMON_STATE_SIT)
			ani = SIMON_ANI_SIT_ATTACK;
		else
		{
			if (climbing && nx == climb_direct)
				ani = SIMON_ANI_GOUP_ATTACK;
			else if (climbing && nx != climb_direct)
				ani = SIMON_ANI_GODOWN_ATTACK;
			else
				ani = SIMON_ANI_ATTACK;
		}
	}
	if (state == SIMON_STATE_SIT)
	{
		if (attacking)
			ani = SIMON_ANI_SIT_ATTACK;
		else
			ani = SIMON_ANI_SIT;
	}
	if (collecting)
		ani = SIMON_ANI_COLLECT;
	if (state == SIMON_STATE_GODOWN)
		ani = SIMON_ANI_GODOWN;
	if (state == SIMON_STATE_GOUP)
		ani = SIMON_ANI_GOUP;
	if (hurting)
		ani = SIMON_ANI_TAKEDAMAGE;
	if (Health <= 0)
	{
		ani = SIMON_ANI_DIE;
		//DebugOut(L"ani :%d --", ani);
	}
	if (state == SIMON_STATE_STANDING_ONSTAIR && !attacking)
	{
		if (nx == climb_direct)
			animations[SIMON_ANI_GOUP]->GetFrame(1)->GetSprite()->Draw(x, y, alpha, nx);
		else
			animations[SIMON_ANI_GODOWN]->GetFrame(1)->GetSprite()->Draw(x, y, alpha, nx);
		return;
	}
	if (ani == SIMON_ANI_DIE && animations[ani]->GetCurrentFrame() == 1 && animations[SIMON_ANI_DIE]->GetFrame(1)->GetSprite()->GetId() == 1026)
	{
		animations[ani]->GetFrame(1)->GetSprite()->Draw(x, y, alpha, nx);
		return;
	}
	if (state == SIMON_STATE_TURN_BACK)
		ani = SIMON_ANI_TURN_BACK;
	animations[ani]->Render(x, y, alpha, nx);
	RenderBoundingBox();
	//DebugOut(L"ani :%d --", ani);
}

void Simon::setcurrentsubWeapondTurnDesc()
{
	if (currentsubWeapondTurn >= 1)
		currentsubWeapondTurn--;
	else
		currentsubWeapondTurn = 0;
}

void Simon::collisionwithenemy(vector<LPGAMEOBJECT> *list)
{
	vector<LPCOLLISIONEVENT> coEvents;

	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(list, coEvents);
	float min_tx, min_ty, nx = 0, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (!untouchable && !invisible)
		{
			Sound::getInstance()->play("hurting", false, 1);
			if (dynamic_cast<Boss*>(e->obj))
			{
				if (nx != 0)
					takedamage(2, -nx);
				else
					takedamage(2, 1);
			}
			else
			{
				if (nx != 0)
					takedamage(1, -nx);
				else
					takedamage(1, 1);
				if (dynamic_cast<Bat *>(e->obj))
					dynamic_cast<Bat *>(e->obj)->takedamage();
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Simon::collisionwithSmallItem(CGameObject * si)
{
	SmallItem *lh = dynamic_cast<SmallItem*>(si);
	switch (lh->getType())
	{

	case Const_Value::small_item_type::smallheart: //small heart
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - SMALL_HEART_BBOX_WIDTH, 0);
		Sound::getInstance()->play("collectitem", false, 1);
		break;
	case Const_Value::small_item_type::largeheart: //large heart
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - LARGE_HEART_BBOX_WIDTH, 0);
		Sound::getInstance()->play("collectitem", false, 1);
		break;
	case Const_Value::small_item_type::whippowerup: // whip power up
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - WHIP_POWER_UP_BBOX_WIDTH, 0);
		this->StartCollect();
		Sound::getInstance()->play("collectweapon", false, 1);
		this->Upgrate();

		break;
	case Const_Value::holywateritem: // holy water
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - HOLYWATER_BBOX_WIDTH, 0);
		if (currentsubwepond == Const_Value::Weapond::holywater)
			this->currentsubWeapondTurn += 5;
		else
			this->currentsubWeapondTurn = 5;
		Sound::getInstance()->play("collectweapon", false, 1);
		currentsubwepond = Const_Value::Weapond::holywater;
		break;
	case Const_Value::small_item_type::sworditem: //sword
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - SWORD_BBOX_WIDTH, 0);
		if (currentsubwepond == Const_Value::Weapond::sword)
			this->currentsubWeapondTurn += 5;
		else
			this->currentsubWeapondTurn = 5;
		Sound::getInstance()->play("collectweapon", false, 1);
		currentsubwepond = Const_Value::Weapond::sword;
		break;
	case Const_Value::small_item_type::axeitem:
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - AXE_BBOX_WIDTH, 0);
		if (currentsubwepond == Const_Value::Weapond::axe)
			this->currentsubWeapondTurn += 5;
		else
			this->currentsubWeapondTurn = 5;
		
			Sound::getInstance()->play("collectweapon", false, 1);
		currentsubwepond = Const_Value::Weapond::axe;
		break;
	case Const_Value::whitemoneybag:
	case Const_Value::redmoneybag:
	case Const_Value::bluemoneybag:
	{
		int randnum = rand() % 4;
		Sound::getInstance()->play("display_monney", false, 1);
		switch (randnum)
		{
		case 0:
			money += 100;
			listeffect->push_back(new Effect(Const_Value::effect_type::money100, lh->getx() + 30, lh->gety(), 0, 0));
			break;
		case 1:
			money += 400;
			listeffect->push_back(new Effect(Const_Value::effect_type::money400, lh->getx() + 30, lh->gety(), 0, 0));
			break;
		case 2:
			money += 700;
			listeffect->push_back(new Effect(Const_Value::effect_type::money700, lh->getx() + 30, lh->gety(), 0, 0));
			break;
		case 3:
			money += 1000;
			listeffect->push_back(new Effect(Const_Value::effect_type::money1000, lh->getx() + 30, lh->gety(), 0, 0));
			break;
		default:
			money += 0;
			break;
		}
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - MONEYBAG_BBOX_WIDTH, 0);
		break;
	}
	case Const_Value::small_item_type::cross:
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - CROSS_BBOX_WIDTH, 0);
		startcollectCross();
		Sound::getInstance()->play("holycross", false, 1);
		break;
	case Const_Value::small_item_type::invisiblepot:
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - INVISIBLEPOT_BBOX_WIDTH, 0);
		startInvisible();
		Sound::getInstance()->play("InvisibilityPotion_Begin", false, 1);
		break;
	case Const_Value::small_item_type::stopwatch:
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - STOPWATCH_BBOX_WIDTH, 0);
		startPause();
		Sound::getInstance()->play("StopWatch", false,1);
		break;
	case Const_Value::small_item_type::doubleshot:
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - DOUBLESHOT_BBOX_WIDTH, 0);
		doubleshot = true;
		Sound::getInstance()->play("collectitem", false, 1);
		break;
	case Const_Value::small_item_type::chicken:
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - CHICKEN_BBOX_WIDTH, 0);
		Health = (Health + 6 > SIMON_DEFAULT_HEALTH) ? SIMON_DEFAULT_HEALTH : (Health + 6);
		doubleshot = true;
		Sound::getInstance()->play("collectitem", false, 1);
		break;
	case Const_Value::small_item_type::ball:
		lh->SetState(ITEM_STATE_UNACTIVE);
		lh->SetPosition(-100 - AXE_BBOX_WIDTH, 0);
		isGameOver = true;
		Sound::getInstance()->play("collectitem", false, 1);
		break;
	default:
		break;
	}
}

void Simon::resetAnimation()
{

	animations[SIMON_ANI_ATTACK]->reset();
	animations[SIMON_ANI_GOUP_ATTACK]->reset();
	animations[SIMON_ANI_GODOWN_ATTACK]->reset();
	animations[SIMON_ANI_SIT_ATTACK]->reset();

	attack_start = 0;
	attacking = false;
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
	case SIMON_STATE_TURN_BACK:
		vx = 0;
		vy = 0;
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

void Simon::comeback()
{
	//DebugOut(L"\nsimon die");
	x = Camera::getInstance()->getstarpositionofcurrentarea();
	Camera::getInstance()->SetFollowtoSimon(true);
	y = OFFSET_Y;
	
	Health = SIMON_DEFAULT_HEALTH;
	Sound::getInstance()->play("bacbackgroundmusic", true, 0);
	Sound::getInstance()->stop("backgroundmusic_boss");
	Sound::getInstance()->stop("Life_Lost");
	resetToDefault();
	vx = 0;
	vy = 0;
	resetAnimation();
	timeDie = 0;
	nx = 1;
}

void Simon::StartAttack()
{
	if (!attacking && !collecting && !hurting) {
		resetAnimation();
		attacking = true;
		attack_start = GetTickCount();
		temp_state = state;
		overlap_time = GetTickCount();
		temp_nx = nx;
		attacwhenjump = (jumpingmono || jumpingplex);
	}

}

void Simon::resetToDefault()
{
	jump_start = 0;
	jumpingmono = false;
	jumpplus_start = 0;
	jumpingplex = false;
	/*hurt_start = 0;
	hurting = false;*/
	state = SIMON_STATE_IDLE;
}

void Simon::StartmonoJump()
{
	if (!jumpingmono && !jumpingplex && !collecting && !attacking && !hurting) {
		jumpingmono = true; jump_start = GetTickCount();
		//onGround = false;
		temp_state = SIMON_STATE_SIT;
	}
}

void Simon::StartplexJump()
{
	if (!jumpingmono && !jumpingplex && !collecting && !attacking && !hurting)
	{

		jumpingplex = true; jumpplus_start = GetTickCount();
		temp_nx = nx;
		//onGround = false;
		temp_state = SIMON_STATE_SIT;
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

void Simon::startAutowalk(int lastdirect, float targetX, float speed)
{
	if (!autoclimbing)
		dofirst = 1;
	speedauto = speed;
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

	//tempx = x;
	//tempy = y;
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
		if (Typestairstart == Const_Value::in_obj_type::stairdown)
		{
			lengthstair += 1.0f;
			numstep = lengthstair / 16;
		}
		else
		{
			lengthstair -= 1.0f;
			numstep = lengthstair / 16;
		}
	}
}

void Simon::startclimbup()
{
	if (canclimbup && !attacking)
	{
		climbing = true;
		nx = climb_direct;
		state = SIMON_STATE_GOUP;
		x += climb_direct * 1.0f;
		y -= 1.0f;
		if (Typestairstart == Const_Value::in_obj_type::stairup)
		{
			lengthstair += 1.0f;
			numstep = lengthstair / 16;
		}
		else
		{
			lengthstair -= 1.0f;
			numstep = lengthstair / 16;
		}
	}
}

void Simon::startFalling()
{
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

int Simon::damageshot()
{
	int shot = 1;
	if (doubleshot)
		shot = 2;
	return shot;
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{

	if (state == SIMON_STATE_SIT || jumpingmono || jumpingplex)
	{
		left = x + (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2;
		top = y + SIMON_SPACING_ONTOP;

		right = left + SIMON_SMALL_BBOX_WIDTH;
		bottom = top + SIMON_SMALL_SIT_BBOX_HEIGHT;
	}
	else
	{
		left = x + (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2;
		top = y + (SIMON_BIG_BBOX_HEIGHT - SIMON_SMALL_BBOX_HEIGHT) / 2;

		right = left + SIMON_SMALL_BBOX_WIDTH;
		bottom = top + SIMON_SMALL_BBOX_HEIGHT - +(SIMON_BIG_BBOX_HEIGHT - SIMON_SMALL_BBOX_HEIGHT) / 2;
	}

}
