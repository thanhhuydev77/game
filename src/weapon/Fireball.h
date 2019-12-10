#pragma once
#include "../sample/GameObject.h"
#include "../map/Invisibleobject.h"
#include "../camera/Camera.h"
class Fireball :
	public CGameObject
{
	float speed;
	bool isfinish;
	float angle;
public:
	Fireball(float x,float y,int directx,float angle = 0);
	bool isFinish() { return isfinish; }
	void setspeed(float s = 0);
	~Fireball();
	void restart(float x, float y, int direct, float angle = 0);
	// Inherited via CGameObject
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

