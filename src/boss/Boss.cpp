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
	if(Health <= 0)
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
	//float x1 = x;
	//float y1 = y;
	float simonleft = simon->getx();
	float simonbottom = simon->gety() + SIMON_BIG_BBOX_HEIGHT;

	if (simonleft < x) // simon bên trái boss
		xTarget = Camera::getInstance()->Getx() - 100 + rand() % ((int)(simonleft - Camera::getInstance()->Getx() + 100));
	else // simon bên phải boss
		xTarget = simonleft + SIMON_BIG_BBOX_WIDTH + rand() % ((int)(Camera::getInstance()->Getx() + Camera::getInstance()->GetWidth() - (simon->getx() + SIMON_BIG_BBOX_WIDTH) + 100));

	yTarget = simonbottom - 50;

	//x3 = xTarget;
	//y3 = yTarget;
	DebugOut(L"xtarget: %d , ytarget :%d", (int)xTarget, (int)yTarget);
	vx = -(x - xTarget) / (abs(xTarget - xBefore)*1000.0f / 150); // vận tốc cần để đi đến Target // quy ước: cứ 1 giây đi 150px
	vy = (yTarget - yBefore) / 650;
	//isUseBezierCurves = true;
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


	vx = (xTarget - xBefore) / (1000); // cho đi 1 giây
	vy = (yTarget - yBefore) / (1000);
}

void Boss::startattack()
{

	DebugOut(L"ATTACK!\n");
	int DirectionWeapon = 0;
	float xAttack = x + BOSS_BBOX_WIDTH / 2;
	float yAttack = y + BOSS_BBOX_HEIGHT / 2;

	float heightwithsimon = simon->gety() + (SIMON_BIG_BBOX_HEIGHT/2) - yAttack;
	float widthwithsimon = abs(simon->getx()+(SIMON_BIG_BBOX_WIDTH/2) - xAttack);
	float angle = heightwithsimon / widthwithsimon;
	DebugOut(L"angle :%f", angle);
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
	//co roi nhung da ket thuc roi
	if (dynamic_cast<Fireball*>(weapon)->isFinish())
	{
		dynamic_cast<Fireball*>(weapon)->restart(xAttack, yAttack, DirectionWeapon, angle);
		dynamic_cast<Fireball*>(weapon)->setspeed(0.12);
	}
	else
		return;

	//// khoảng cách đạn bắn trúng simon
	//float S = sqrt((xAttack - simon->getx()) *(xAttack - simon->getx()) + (yAttack - simon->gety())*(y - simon->gety())); //s=sqrt(x^2+y^2)

	//// thời gian bắn trúng nếu dùng vận tốc FIREBALL_SPEED
	//float t = S / FIREBALL_SPEED;

	//weapon->SetSpeed(DirectionWeapon* abs(xAttack - simon->getx()) / t, abs(yAttack - simon->gety()) / t);
	//weapon->Attack(xAttack, yAttack, 1);

	processstate = BOSS_PROCESS_ATTACK;

	//DebugOut(L"vx = %f , vy = %f , isFinish = %d\n", weapon->GetVx(), weapon->GetVy(), weapon->GetFinish());


	//DebugOut(L"!------------------------!\n\n");

	//Sound::GetInstance()->Play(eSound::soundHit);

	TimeWaited = 0;
	isWaiting = true;
}

void Boss::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	DebugOut(L"\nboss health:%d \n",Health);
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
		/*case BOSS_PROCESS_SLEEP:
		{

			break;
		}
	*/
	case BOSS_PROCESS_START_1: // đi xuống
	{
		DebugOut(L"start 1\n");
		// bắt đầu thì đi xuống 1 đoạn ngắn
		if (y >= yTarget)
		{
			vy = 0;
			processstate = BOSS_PROCESS_START_2; // qua trạng thái di chuyển đến cửa sổ

			xBefore = x;
			yBefore = y;

			xTarget = 5480;
			yTarget = 201;

			vx = ((xTarget - xBefore) / (1500.0f)); // Vận tốc cần để đi đến target trong 1.5s
			vy = 0.12f; // tạo độ cong
		}
		break;
	}

	case BOSS_PROCESS_START_2: // đi cong xuống ngay cửa sổ
	{
		DebugOut(L"start 2\n");
		if (!isWaiting)
		{
			// tạo độ cong
			vy -= 0.0001f * dt;
			if (vy < 0)
				vy = 0;
			// tạo độ cong

			if (x >= xTarget) // di chuyển xong đến mục tiêu 2
			{
				vx = 0;
				vy = 0;
				isWaiting = true; // bật trạng thái chờ
				TimeWaited = 0; // reset lại time đã chờ
			}
		}
		else
		{
			TimeWaited += dt;
			if (TimeWaited >= (UINT)(2000 + rand() % 1500))
			{
				isWaiting = false; // ngừng chờ

				start_curving();
			}
		}


		break;
	}

	case BOSS_PROCESS_CURVES:
	{
		DebugOut(L"curving\n");

		if (abs(x - xBefore) >= abs(xTarget - xBefore)) // đi xong thid đi thẳng
		{
			vx = 0;
			vy = 0;
			isUseBezierCurves = false;

			startstraight();

			break;
		}
		vy -= 0.0001f*dt;
		if (vy <= 0 || y >= yTarget)
			vy = 0;
		else
			vy += (y - yTarget) / 50000;
		DebugOut(L"\nvy curve: %f", vy);
		break;
	}

	case BOSS_PROCESS_STRAIGHT_1:
	{
		DebugOut(L"straign1 1\n");
		if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
			abs(y - yBefore) >= abs(yTarget - yBefore)) // đi xong thì đi thẳng theo hướng random
		{
			vx = vy = 0;

			startstraight();

		}
		break;
	}

	case BOSS_PROCESS_STRAIGHT_2:
	{DebugOut(L"straign 2\n");
	if (!isWaiting)
	{
		if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
			abs(y - yBefore) >= abs(yTarget - yBefore)) // đi xongthì dừng
		{
			vx = vy = 0;


			isWaiting = true; // bật trạng thái chờ
			TimeWaited = 0; // reset lại time đã chờ
		}
	}
	else
	{
		TimeWaited += dt;
		if (TimeWaited >= 3000)
		{
			isWaiting = false; // ngừng chờ

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
		else
		{
			//ProcessSmart();
		}
	}


	break;
	}

	case BOSS_PROCESS_ATTACK:
	{
		DebugOut(L"attack \n");
		if (isWaiting)
		{
			TimeWaited += dt;
			if (TimeWaited >= 1500)
			{
				isWaiting = false; // ngừng chờ
				startstraight(); // qua trạng thái đi thẳng
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
			isUseBezierCurves = false;
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

	 if (disappearing)
		{
		animations[2]->Render(x , y, 255);
		animations[2]->Render(x +18, y, 255);
		animations[2]->Render(x + 32, y, 255);
		animations[2]->Render(x, y+32, 255);
		animations[2]->Render(x + 18, y+32, 255);
		animations[2]->Render(x + 32, y+32, 255);

		}
	 else {
		 if (state == BOSS_STATE_SLEEP)
			 animations[0]->Render(x, y, 255);
		 else
			 if (state == BOSS_STATE_WAKE)
				 animations[1]->Render(x, y, 255);
	 }
}
