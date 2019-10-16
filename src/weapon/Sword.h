#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Sprites.h"
#include "../sample/Const_Value.h"
#include "../map/CBratizer.h"
#include <vector>
#include "../item/Large_heart.h"
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

