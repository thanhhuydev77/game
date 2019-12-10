#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../camera/Camera.h"
class Boss :
	public CGameObject
{
	float xBefore;
	float yBefore;
	int processstate;
	float xTarget;
	float yTarget;
	DWORD TimeWaited; 
	bool isUseBezierCurves;
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

