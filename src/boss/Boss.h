#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../camera/Camera.h"
class Boss :
#define ANI_WAKE   1
#define ANI_SLEEP  0
#define	ANI_FLAME  2
	public CGameObject
{
	float xBefore;
	float yBefore;
	int processstate;
	float xTarget;
	float yTarget;
	DWORD TimeWaited; 
	bool isWaiting;
	CGameObject *simon;
	CGameObject * weapon;
	CGameObject *subItem;
	DWORD disappear_start, TimeAttack;
	bool disappearing;
	vector <CGameObject*> * listWeaponOfEnemy;
public:
	Boss(CGameObject * simon,vector <CGameObject*> * listWeaponOfEnemy);
	~Boss();
	void start_disappear();
	void addSubItem(CGameObject *sub) { subItem = sub; };
	void takedamage(int damage);
	bool Isdied() { return (Health <= 0); }
	void reset();
	void startup();
	void start_curving();
	void startstraight();
	void startattack();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	// Inherited via CGameObject
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
	bool xzy() {};
};

