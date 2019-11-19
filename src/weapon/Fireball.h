#pragma once
#include "../sample/GameObject.h"
#include "../map/Invisibleobject.h"
#include "../camera/Camera.h"
class Fireball :
	public CGameObject
{
	bool isfinish;
public:
	Fireball(float x,float y,int direct);
	bool isFinish() { return isfinish; }
	~Fireball();
	void restart(float x, float y, int direct);
	// Inherited via CGameObject
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

