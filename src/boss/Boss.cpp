#include "Boss.h"



Boss::Boss(CGameObject * simon, vector <CGameObject*> * listWeaponOfEnemy)
{

	LoadResourceHelper::Loadspritefromfile("content\\boss\\boss_sprite.txt", ID_TEX_BOSS);
	LoadResourceHelper::Loadanimationfromfile("content\\boss\\boss_ani.txt", this);

	LoadResourceHelper::Loadspritefromfile("content\\effect\\flame_sprite.txt", ID_TEX_FLAME);
	LoadResourceHelper::Loadanimationfromfile("content\\effect\\flame_ani.txt", this);
	this->simon = simon;
	this->listWeaponOfEnemy = listWeaponOfEnemy;

	reset();

}


Boss::~Boss()
{
}

void Boss::start_disappear()
{
	disappearing = true;
	disappear_start = GetTickCount();

}

void Boss::takedamage(int damage)
{
	Health -= damage;
	if (Health <= 0)
		start_disappear();
}

void Boss::reset()
{
	DebugOut(L"\nreset");
	vx = 0;
	vy = 0;
	state = BOSS_STATE_UNACTIVE;
	x = PHANTOMBAT_DEFAULT_X;
	y = PHANTOMBAT_DEFAULT_Y;

	Health = PHANTOMBAT_DEFAULT_HEALTH;
	processstate = 0;
	disappearing = false;
	xBefore = x;
	yBefore = y;
	isWaiting = false;
}

void Boss::startup()
{
	if (state == BOSS_STATE_WAKE)
		return;
	if (Isdied())
		return;
	state = BOSS_STATE_WAKE;
	processstate = BOSS_PROCESS_START_1;
	xBefore = x;
	yBefore = y;
	vy = 0.05f;
	vx = 0.0f;
	yTarget = y + 40;
}

void Boss::start_curving()
{
	xBefore = x;
	yBefore = y;
	float simonleft = simon->getx();
	float simonbottom = simon->gety() + SIMON_BIG_BBOX_HEIGHT;

	if (simonleft < x) // simon on left boss
		xTarget = Camera::getInstance()->Getx() - 100 + rand() % ((int)(simonleft - Camera::getInstance()->Getx() + 100));
	else // simon on right boss
		xTarget = simonleft + SIMON_BIG_BBOX_WIDTH + rand() % ((int)(Camera::getInstance()->Getx() + Camera::getInstance()->GetWidth() - (simon->getx() + SIMON_BIG_BBOX_WIDTH) + 100));
	yTarget = simonbottom - 50;
	//DebugOut(L"xtarget: %d , ytarget :%d", (int)xTarget, (int)yTarget);
	vx = -(x - xTarget) / (abs(xTarget - xBefore)*1000.0f / 150); // vận tốc cần để đi đến Target // quy ước: cứ 1 giây đi 150px
	vy = (yTarget - yBefore) / 650;
	processstate = BOSS_PROCESS_CURVES;
}

void Boss::startstraight()
{
	switch (processstate)
	{
	case BOSS_PROCESS_STRAIGHT_1:
		processstate = BOSS_PROCESS_STRAIGHT_2;
		break;
	default:
		processstate = BOSS_PROCESS_STRAIGHT_1;
		break;
	}
	xBefore = x;
	yBefore = y;
	xTarget = (float)PHANTOMBAT_BOUNDARY_START_STAIGHT_LEFT + rand() % (PHANTOMBAT_BOUNDARY_START_STAIGHT_RIGHT - PHANTOMBAT_BOUNDARY_START_STAIGHT_LEFT);
	yTarget = 180.0f + rand() % (190 - 80);

	//	DebugOut(L"StatusProcessing = %d, Target (%f, %f) \n", StatusProcessing, xTarget, yTarget);
	vx = (xTarget - xBefore) / (1000);
	vy = (yTarget - yBefore) / (1000);
}

void Boss::startattack()
{

	DebugOut(L"ATTACK!\n");
	int DirectionWeapon = 0;
	float xAttack = x + BOSS_BBOX_WIDTH / 2;
	float yAttack = y + BOSS_BBOX_HEIGHT / 2;

	float heightwithsimon = simon->gety() + (SIMON_BIG_BBOX_HEIGHT / 2) - yAttack;
	float widthwithsimon = abs(simon->getx() + (SIMON_BIG_BBOX_WIDTH / 2) - xAttack);
	float angle = heightwithsimon / widthwithsimon;
	//DebugOut(L"angle :%f", angle);
	if (xAttack < simon->getx())
		DirectionWeapon = 1;
	else
	{
		DirectionWeapon = -1;
	}
	if (weapon == NULL)
	{
		weapon = new Fireball(xAttack, yAttack, DirectionWeapon, angle);
		listWeaponOfEnemy->push_back(weapon);
		dynamic_cast<Fireball*>(weapon)->setspeed(0.12);
	}
	//finish --> restart
	if (dynamic_cast<Fireball*>(weapon)->isFinish())
	{
		dynamic_cast<Fireball*>(weapon)->restart(xAttack, yAttack, DirectionWeapon, angle);
		dynamic_cast<Fireball*>(weapon)->setspeed(0.12);
	}
	else
		return;
	processstate = BOSS_PROCESS_ATTACK;

	TimeWaited = 0;
	isWaiting = true;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"\nboss health:%d \n", Health);
	if (state != BOSS_STATE_WAKE)
		return;
	if (disappearing)
	{
		if (GetTickCount() - disappear_start > 300)
		{
			disappearing = false;
			disappear_start = 0;
			state = BOSS_STATE_UNACTIVE;
			if (subItem != nullptr)
			{
				subItem->SetState(ITEM_STATE_ACTIVE);
				subItem->SetPosition(x, y);
			}
		}
	}
	if (Health <= 0)
		return;
	switch (processstate)
	{
	case BOSS_PROCESS_START_1:
	{
		//DebugOut(L"start 1\n");
		if (y >= yTarget)
		{
			vy = 0;
			processstate = BOSS_PROCESS_START_2;

			xBefore = x;
			yBefore = y;

			xTarget = x + 190;
			yTarget = y + 51;

			vx = ((xTarget - xBefore) / (1500.0f));
			vy = 0.12f;
		}
		break;
	}
	case BOSS_PROCESS_START_2:
	{
		//DebugOut(L"start 2\n");
		if (!isWaiting)
		{
			vy -= 0.0001f * dt;
			if (vy < 0)
				vy = 0;

			if (x >= xTarget)
			{
				vx = 0;
				vy = 0;
				isWaiting = true;
				TimeWaited = 0;
			}
		}
		else
		{
			TimeWaited += dt;
			if (TimeWaited >= (UINT)(2000 + rand() % 1500))
			{
				isWaiting = false;

				start_curving();
			}
		}


		break;
	}

	case BOSS_PROCESS_CURVES:
	{
		//DebugOut(L"curving\n");

		if (abs(x - xBefore) >= abs(xTarget - xBefore))
		{
			vx = 0;
			vy = 0;

			startstraight();

			break;
		}
		vy -= 0.0001f*dt;
		if (vy <= 0 || y >= yTarget)
			vy = 0;
		else
			vy += (y - yTarget) / 50000;
		//DebugOut(L"\nvy curve: %f", vy);
		break;
	}

	case BOSS_PROCESS_STRAIGHT_1:
	{
		DebugOut(L"straign1 1\n");
		if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
			abs(y - yBefore) >= abs(yTarget - yBefore))
		{
			vx = vy = 0;

			startstraight();

		}
		break;
	}

	case BOSS_PROCESS_STRAIGHT_2:
	{
		DebugOut(L"straign 2\n");
		if (!isWaiting)
		{
			if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
				abs(y - yBefore) >= abs(yTarget - yBefore))
			{
				vx = vy = 0;


				isWaiting = true;
				TimeWaited = 0;
			}
		}
		else
		{
			TimeWaited += dt;
			if (TimeWaited >= 3000)
			{
				isWaiting = false;

				int random = rand() % 3;
				switch (random)
				{
				case 0: //33 %
					startattack();
					break;

				default: // 66%
					start_curving();
					break;
				}
			}
		}
		break;
	}

	case BOSS_PROCESS_ATTACK:
	{
		//DebugOut(L"attack \n");
		if (isWaiting)
		{
			TimeWaited += dt;
			if (TimeWaited >= 1500)
			{
				isWaiting = false;
				startstraight();
			}
		}
		break;
	}


	default:
		break;
	}
	if (simon->Health <= 0)
		reset();
	CGameObject::Update(dt);
	x += dx;
	y += dy;


	if (!Camera::getInstance()->checkOutCamera(x, y, x + BOSS_BBOX_WIDTH, y + BOSS_BBOX_HEIGHT)) // ra khỏi cam thì xử lí hướng tiếp theo
	{
		switch (processstate)
		{
		case BOSS_PROCESS_CURVES:
		{
			startstraight();
			break;
		}

		case BOSS_PROCESS_STRAIGHT_1:
		{
			startstraight();
			break;
		}

		case BOSS_PROCESS_STRAIGHT_2:
		{
			int random = rand() % 3;
			switch (random)
			{
			case 0: //33 %
				startattack();
				break;

			default: // 66%
				start_curving();

				break;
			}

			break;
		}
		}

	}

}

void Boss::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == BOSS_STATE_WAKE)
	{
		left = x;
		top = y;
		right = left + BOSS_BBOX_WIDTH;
		bottom = top + BOSS_BBOX_HEIGHT;
	}
	else
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}
}

void Boss::Render()

{
	if (!Camera::getInstance()->checkInCamera(x, y, x + BOSS_BBOX_WIDTH, y + BOSS_BBOX_HEIGHT))
	{
		return;
	}
	if (disappearing)
	{
		animations[ANI_FLAME]->Render(x, y, 255);
		animations[ANI_FLAME]->Render(x + FLAME_WIDTH, y, 255);
		animations[ANI_FLAME]->Render(x + 2*FLAME_WIDTH, y, 255);
		animations[ANI_FLAME]->Render(x, y + FLAME_HEIGHT, 255);
		animations[ANI_FLAME]->Render(x + FLAME_WIDTH, y + FLAME_HEIGHT, 255);
		animations[ANI_FLAME]->Render(x + 2 * FLAME_WIDTH, y + FLAME_HEIGHT, 255);

	}
	else {
		if (state == BOSS_STATE_SLEEP)
			animations[ANI_SLEEP]->Render(x, y, 255);
		else
			if (state == BOSS_STATE_WAKE)
				animations[ANI_WAKE]->Render(x, y, 255);
	}
}
