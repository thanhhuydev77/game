#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include <string>
#include "../sample/Const_Value.h"
#include "../map/CBratizer.h"
#include "../map/Brick.h"
#include "../weapon/Whip.h"
#include "../item/Large_heart.h"
#include "../item/Whip_PowerUp.h"
#include "../item/SwordItem.h"
using namespace std;
class Simon : public CGameObject
{
		bool onstate;
		bool attacking;
		bool collecting;
		bool jumping;
		int untouchable;
		DWORD untouchable_start;
		DWORD collect_start;
		DWORD overlap_time;
		DWORD attack_start;
		DWORD jump_start;
		DWORD jumpplus_start;
		int temp_nx;
		int sword_turn;
public:
	Simon(double scalerate = 1);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void setswordturndesc() ;
	bool isattacking() { return attacking; }
	int getswordturn() { return sword_turn; }
	bool isOnState() { return onstate; };
	bool iscollecting() { return collecting; }
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartAttack();
	void StartmonoJump();
	void StartplexJump();
	void StartCollect();
	void Upgrate();
	int getlevel() { return level; }
	int GetDirect();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

