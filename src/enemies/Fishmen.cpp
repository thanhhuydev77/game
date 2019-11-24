#include "Fishmen.h"



Fishmen::Fishmen(float X, float Y, int Direction, CGameObject* simon, vector<CGameObject*> *listWeaponOfEnemy, vector<CGameObject*> *listeffect)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\enemies\\fishman_sprite.txt", ID_TEX_FISHMEN);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\enemies\\fishman_ani.txt", this);

	LoadResourceHelper::Loadspritefromfile("content\\effect\\flame_sprite.txt", ID_TEX_FLAME);
	LoadResourceHelper::Loadanimationfromfile("content\\effect\\flame_ani.txt", this);
	this->x = X;
	this->y = Y;
	OrginalX = x;
	OrginalY = y;
	Health = 1;
	this->nx = Direction;
	this->simon = simon;
	this->listWeaponOfEnemy = listWeaponOfEnemy;
	vy = -FISHMEN_SPEED_Y_UP;
	state = ENEMY_STATE_LIVE;
	this->listeffect = listeffect;
}


Fishmen::~Fishmen()
{
}

void Fishmen::start_disappear()
{
	disappearing = true;
	disappear_start = GetTickCount();
}

void Fishmen::takedamage()
{
	state = ENEMY_STATE_DIE;
	start_disappear();
	vx = 0;
	vy = 0;
}

void Fishmen::Attack()
{
	//init when null
	if (Fire == NULL)
	{
		Fire = new Fireball(x + 10, y + 3, nx);
		listWeaponOfEnemy->push_back(Fire);
	}
	//co roi nhung da ket thuc roi
	if (dynamic_cast<Fireball*>(Fire)->isFinish())
	{
		dynamic_cast<Fireball*>(Fire)->restart(x + 10, y + 3, nx);
	}
	else
		return;
	isAttacking = true;
	TimeAttack = GetTickCount();
}

void Fishmen::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += FISHMEN_GRAVITY * dt;
	if (disappearing)
	{
		if (GetTickCount() - disappear_start > 300)
		{
			disappearing = false;
			disappear_start = 0;
			Health -= 1;
			if (subItem != nullptr)
				subItem->SetState(ITEM_STATE_ACTIVE);

			//delete(this);
		}
	}
	else
	{
		if (Isdied())
			return;
		float t, l, r, b;
		GetBoundingBox(l, t, r, b);
		RECT check;
		check.left = l;
		check.top = t;
		check.right = r;
		check.bottom = b;
		// still in camera
		if (!Camera::getInstance()->checkInCamera(check))
			Health = 0;
		if (y > OrginalY)
			Health = 0;
		//falling down
		if (y <= OrginalY - FISHMEN_DY_JUMP)
		{
			vy = FISHMEN_SPEED_Y_DOWN;
		}

		//walking enough --> rotate nx
		if (abs(x - OrginalX) >= FISHMEN_DX_LIMIT)
		{
			if ((nx == -1 && !(simon->getx() < x)) || (nx == 1 && !(x < simon->getx())))
			{
				//rotate nx
				nx *= -1;
				//reset orginal x
				OrginalX = x;
			}
		}
		//walking enough --> attack
		if (XaccumulationAttack >= FISHMEN_DX_ATTACK_LIMIT)
		{
			XaccumulationAttack = 0;
			Attack();
		}

		XBefore = x;
		if (walking)
		{
			vx = nx * FISHMEN_SPEED_X;
			vy += FISHMEN_GRAVITY;
		}
		CGameObject::Update(dt);
		if ((abs((int)y - WATER_LEVEL_HEIGHT) < 5 && vy < 0 ))
		{
			listeffect->push_back(new Effect(Const_Value::effect_type::water, x, y-30, -0.15f, 0.15f));
			listeffect->push_back(new Effect(Const_Value::effect_type::water, x+FISHMEN_BBOX_WIDTH, y-30,0.15f, 0.15f));
		}
		
			if ((abs((int)y + FISHMEN_BBOX_HEIGHT - WATER_LEVEL_HEIGHT) < 5 && vy > 0))
			{
				listeffect->push_back(new Effect(Const_Value::effect_type::water, x, y +FISHMEN_BBOX_HEIGHT- 30, -0.15f, 0.15f));
				listeffect->push_back(new Effect(Const_Value::effect_type::water, x + FISHMEN_BBOX_WIDTH, y+FISHMEN_BBOX_HEIGHT - 30, 0.15f, 0.15f));
			}
#pragma region Xu li va cham Brick
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		vector<LPGAMEOBJECT> list_Brick;
		list_Brick.clear();

		for (UINT i = 0; i < coObjects->size(); i++)
			if (dynamic_cast<CInvisibleObject*>(coObjects->at(i)) && dynamic_cast<CInvisibleObject*>(coObjects->at(i))->Gettype() == Const_Value::Brick)
				list_Brick.push_back(coObjects->at(i));

		CalcPotentialCollisions(&list_Brick, coEvents);
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (nx != 0)
		{
			this->nx *= -1;
		}
		if (ny == -1)
		{
			vy = 0;
			y += min_ty * dy + ny * 0.4f;
			walking = true;
		}
		else
		{
			y += dy;
		}

		if (!isAttacking) 
		{
			bool isCollisionDirectionX = false;
			for (UINT i = 0; i < coEventsResult.size(); i++) 
			{
				if (coEventsResult[i]->nx != 0)
				{
					CInvisibleObject * brick = dynamic_cast<CInvisibleObject*>(coEventsResult[i]->obj);
					{
						x += min_tx * dx + nx * 0.4f;
						nx *= -1;
						isCollisionDirectionX = true;
					}
				}
			}

			if (!isCollisionDirectionX) 
				x += dx;
		}


		for (UINT i = 0; i < coEvents.size(); i++)
			delete coEvents[i];
#pragma endregion
		if (isAttacking)
		{
			DWORD now = GetTickCount();
			if (now - TimeAttack >= FISHMEN_TIME_LIMIT_WAIT_AFTER_ATTACK)
			{
				isAttacking = false;
			}
		}

		XAfter = x;
		XaccumulationAttack += abs(XAfter - XBefore);
		//DebugOut(L"y :%d,vy :%d \n", (int)y, (int)vy);
	}
}

void Fishmen::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + FISHMEN_BBOX_WIDTH;
	bottom = top + FISHMEN_BBOX_HEIGHT;
}

void Fishmen::Render()
{
	if (Health <= 0)
		return;
	if (disappearing)
		animations[3]->Render(x - 10, y + 3, 255);
	else
		if (walking)
			animations[1]->Render(x, y, 255, nx);
		else if (shooting)
			animations[2]->Render(x, y, 255, nx);
		else
			animations[0]->Render(x, y, 255, nx);
}
