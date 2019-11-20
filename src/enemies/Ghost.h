#pragma once
#include "../sample/GameObject.h"
#include "../map/Invisibleobject.h"
#include "../camera/Camera.h"
class Ghost :
	public CGameObject
{
	DWORD disappear_start;
	bool disappearing;
	CGameObject *subItem ;
public:
	Ghost(float X, float Y, int Direction);
	~Ghost();
	int getx() { return x; }
	void start_disappear();
	void addSubItem(CGameObject *sub) { subItem = sub; };
	void takedamage();
	bool Isdied() { return (Health <= 0); }
	// Inherited via CGameObject
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

