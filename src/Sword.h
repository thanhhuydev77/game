#pragma once
#include "GameObject.h"
#include "LoadResourceHelper.h"
#include "Sprites.h"
#include "Const_Value.h"
#include "CBratizer.h"
#include <vector>
#include "Large_heart.h"
using namespace std;

class Sword : public CGameObject
{
	CGameObject* owner;
	DWORD attack_start;
	int turn;
public:
	void setstate(int state) { this->state = state; }
	CGameObject* GetOwner();
	void UpdatePositionRelateToObject(DWORD dt);
	void StartAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	Sword();
	Sword(double scalerate = 1, CGameObject * owner = NULL);
	// Inherited via CGameObject
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom);
	virtual void Render();
	void Render(double scale_rate);
};

