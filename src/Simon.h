#pragma once
#include "GameObject.h"
#include "LoadResourceHelper.h"
#include <string>
#include "Const_Value.h"
#include "CBratizer.h"
#include "Brick.h"
#include "Whip.h"
#include "Large_heart.h"
#include "Whip_PowerUp.h"
#include "SwordItem.h"
using namespace std;
class Simon : public CGameObject
{
		bool onstate;
		bool attacking;
		bool jumping;
		int untouchable;
		DWORD untouchable_start;
		DWORD overlap_time;
		DWORD attack_start;
		DWORD jump_start;
		DWORD jumpplus_start;
		double scale_rate;
		int temp_nx;
		int sword_turn;
public:
	Simon(double scalerate = 1);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void setswordturndesc() { if (sword_turn >= 1) sword_turn--; };
	int getswordturn() { return sword_turn; }
	bool isOnState() { return onstate; };
	void SetState(int state);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartAttack();
	void StartmonoJump();
	void StartplexJump();
	void Upgrate();
	int getlevel() { return level; }
	int GetDirect();
	virtual void Render(double Scale_rate=1);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

