#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Sprites.h"
#include "../sample/Const_Value.h"
#include "../map/CBratizer.h"
#include <vector>
#include "../item/Large_heart.h"
using namespace std;

class Whip : public CGameObject 
{
	CGameObject* owner;
	int level;
	DWORD attack_start;
public:
	Whip();
	Whip(double scalerate = 1, CGameObject * owner = NULL);
	int GetLevel();
	void setstate(int state) { this->state = state; }
	CGameObject* GetOwner();
	void UpdatePositionRelateToObject(DWORD dt);
	void Upgrade();
	void StartAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	virtual void Render();
};

