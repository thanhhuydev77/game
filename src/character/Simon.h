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
using namespace std;
class Simon : public CGameObject
{
	static Simon* _instance;
		bool onGround;
		bool standingonstair;
		bool autowalking;
		bool autoclimbing;
		bool attacking;
		bool collecting;
		bool jumping;
		bool climbing;
		int untouchable;
		bool canclimbup;
		bool canclimbdown;
		DWORD untouchable_start;
		DWORD collect_start;
		DWORD overlap_time;
		DWORD attack_start;
		DWORD jump_start;
		DWORD jumpplus_start;
		int temp_nx;
		int temp_ny;
		int climb_direct;
		int sword_turn;
		bool endmap1;
		int last_nx;
		int climbbing_distance = 0;
		float orginX;
		float orginY;

		float tempx;
		float tempy;
		float targetX;
		float targetY;
		bool canclimb;
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
	bool isOnStair() { return onGround; };
	bool iscollecting() { return collecting; }
	void setclimbing(bool is) { climbing = is; if(!is) canclimbdown = canclimbup = false;
	}
	void reset();
	bool isclimbing() { return climbing; }
	bool iscanclimbup() { return canclimbup; }
	bool iscanclimbdown() { return canclimbdown; }
	void SetState(int state);
	void setcanclimb(bool icanclimb, bool up);
	bool inAutoMode() { return (autoclimbing || autowalking); }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartAttack();
	void StartmonoJump();
	void StartplexJump();
	void StartCollect();
	void startclimbup();
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
	int getx() { return x; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

