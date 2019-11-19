#pragma once
#include "../sample/GameObject.h"
#include "../map/Invisibleobject.h"
class Bat :
	public CGameObject
{
	DWORD disappear_start;
	bool disappearing;
	float yBackup;
	CGameObject *subItem;
public:
	Bat(float X = 0, float Y = 0, int Direction = -1);
	~Bat();
	int getx() { return x; }
	void addSubItem(CGameObject *sub) { subItem = sub; };
	void start_disappear();
	void takedamage();
	bool Isdied() { return (Health <= 0); }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);


	// Inherited via CGameObject
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;

	virtual void Render() override;

};

