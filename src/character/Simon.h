#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include <string>
#include "../sample/Endpoint.h"
#include "../sample/Const_Value.h"
#include "../item/BoundItem.h"
#include "../map/Invisibleobject.h"
#include "../weapon/Whip.h"
#include "../item/SmallItem.h"
#include "../item/Whip_PowerUp.h"
#include "../item/SwordItem.h"
#include "../sample/debug.h"
#include "../item/BoundItem.h"
#include "../item/StaticObject.h"
#include "../camera/Camera.h"
#include "../enemies/Bat.h"
#include "../enemies/Fishmen.h"
#include "../enemies/Ghost.h"
#include "../enemies/Panther.h"

using namespace std;
class Simon : public CGameObject
{
	static Simon* _instance;
	int NumofLife;
		bool onGround;
		bool standingonstair;
		bool autowalking;
		bool autoclimbing;
		bool attacking;
		bool collecting;
		bool jumpingmono;
		bool jumpingplex;
		bool climbing;
		int untouchable;
		bool canclimbup;
		bool canclimbdown;
		bool hurting;
		int Hurtdirect;
		DWORD timeDie;
		DWORD hurt_start;
		DWORD untouchable_start;
		DWORD collect_start;
		DWORD overlap_time;
		DWORD attack_start;
		DWORD jump_start;
		DWORD jumpplus_start;
		float temp_vx;
		int temp_nx;
		int temp_ny;
		int climb_direct;
		
		int sword_turn;
		int money;
		int axe_turn;

		bool endmap1;
		int last_nx;
		int climbbing_distance = 0;
		float orginX;
		float orginY;
		int temp_state;
		float tempx;
		float tempy;
		float targetX;
		float targetY;
		bool canclimb;
		int currentWeapond;
		int dofirst;
		Simon();
public:
	void setclimbingdistance(int cd) { climbbing_distance = cd; }
	static Simon* getinstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void setswordturndesc() ;
	bool isattacking() { return attacking; }
	int getswordturn() { return sword_turn; }
	bool iscollecting() { return collecting; }
	void setclimbing(bool is) { climbing = is; if(!is) canclimbdown = canclimbup = false;
	}
	bool ishurting() { return hurting; }
	void takedamage(int damage,int direct );
	bool isgameover() { return NumofLife <= 0; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartHurting(int direct ) { hurting = 1; hurt_start = GetTickCount(); temp_nx = direct; }
	void collisionwithSmallItem(CGameObject *si);
	bool isJumping() { return (jumpingmono || jumpingplex); }
	bool isOnGround() { return onGround; }
	void resetAnimation();
	bool isclimbing() { return climbing; }
	bool iscanclimbup() { return canclimbup; }
	bool iscanclimbdown() { return canclimbdown; }
	bool attacwhenjump;
	void SetState(int state);
	void setcanclimb(bool icanclimb, bool up);
	bool inAutoMode() { return (autoclimbing || autowalking); }
	void comeback();
	void StartAttack();
	void resetToDefault();
	void StartmonoJump();
	void StartplexJump();
	void StartCollect();
	void startclimbup();
	void startFalling();
	void startclimbdown();
	void startAutowalk(int lastdirect,float targetX);
	void startAutoClimb(int lastdirect,float targetY);
	void Upgrate();
	void setstateendmap1(bool signal) { endmap1 = signal; }
	bool isendmap1() { return endmap1; }
	int getlevel() { return level; }
	int GetDirect();
	void setTempnx(int temp) { temp_nx = temp; }
	void setTempny(int temp) { if (temp == 2) temp_ny = -1; else if (temp == 3) temp_ny = 1; }
	void setcurrentWeapond(int wea) { currentWeapond = wea; }
	bool getcurrentWeapond() { return currentWeapond; }
	int getx() { return x; }
	int gety() { return y; }
	int getVx() { return (int)vx; };
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

