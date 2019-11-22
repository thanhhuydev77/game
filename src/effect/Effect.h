#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
class Effect :public CGameObject
{
	int Type;
	DWORD timestart;
	bool finish;
public:
	Effect(int type,float x,float y,float vx,float vy);
	~Effect();
	bool Isfinish() { return finish; }
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	// Inherited via CGameObject
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

