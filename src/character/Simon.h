#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include <string>
#include "../sample/Endpoint.h"
#include "../sample/Const_Value.h"
#include "../item/CBratizer.h"
#include "../map/Invisibleobject.h"
#include "../weapon/Whip.h"
#include "../item/Large_heart.h"
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
		int climb_direct;
		int sword_turn;
		bool endmap1;
		int last_nx;
		float targetX;
		float targetY;
		bool canclimb;
		int dofirst;
		Simon();
public:
	
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
	void startAutoClimb(int lastdirect, float targetX,float targetY);
	void Upgrate();
	void setstateendmap1(bool signal) { endmap1 = signal; }
	bool isendmap1() { return endmap1; }
	int getlevel() { return level; }
	int GetDirect();
	int getx() { return x; }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

