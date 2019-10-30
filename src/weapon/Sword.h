#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Sprites.h"
#include "../sample/Const_Value.h"
#include "../item/CBratizer.h"
#include <vector>
#include "../item/Large_heart.h"
using namespace std;

class Sword : public CGameObject
{
	CGameObject* owner;
	DWORD attack_start;
	bool attacking;
	bool waiting;
public:
	Sword();
	Sword( CGameObject * owner = NULL);
	void setstate(int state) { this->state = state; }
	CGameObject* GetOwner();
	void UpdatePositionRelateToObject(DWORD dt);
	void StartAttack();
	bool isattacking() { return attacking; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();
};
