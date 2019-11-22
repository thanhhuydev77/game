#pragma once
#include "../sample/GameObject.h"
#include "../weapon/Fireball.h"
#include "../map/Invisibleobject.h"
#include "../effect/Effect.h"
class Fishmen :
	public CGameObject
{
	float OrginalX; 
	float OrginalY;

	float XBefore;
	float XAfter;
	float XaccumulationAttack;
	DWORD disappear_start, TimeAttack;
	bool disappearing;
	CGameObject *simon;
	CGameObject *subItem;
	CGameObject *Fire;
	bool walking, shooting, isAttacking;
	vector<CGameObject*> *listWeaponOfEnemy;
	vector<CGameObject*> *listeffect;
public:
	Fishmen(float X, float Y, int Direction, CGameObject* simon, vector<CGameObject*> *listWeaponOfEnemy, vector<CGameObject*> *listeffect);
	~Fishmen();
	int getx() { return x; }
	void start_disappear();
	void addSubItem(CGameObject *sub) { subItem = sub; };
	void takedamage();
	bool Isdied() { return (Health <= 0); }
	void Attack();
	// Inherited via CGameObject
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

