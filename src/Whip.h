#pragma once
#include "GameObject.h"
#include "LoadResourceHelper.h"
#include "Sprites.h"
#include "Const_Value.h"
#include "CBratizer.h"
#include <vector>
#include "Large_heart.h"
using namespace std;

class Whip : public CGameObject 
{
	CGameObject* owner;
	int level;
	DWORD attack_start;
public:
	int GetLevel();
	void setstate(int state) { this->state = state; }
	CGameObject* GetOwner();
	void UpdatePositionRelateToObject(DWORD dt);
	void Upgrade();
	void StartAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	Whip();
	Whip(double scalerate = 1, CGameObject * owner = NULL);
	// Inherited via CGameObject
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	virtual void Render();
	void Render(double scale_rate);
};

