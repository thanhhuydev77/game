#pragma once
#include "../sample/GameObject.h"
#include "../map/Invisibleobject.h"
#include "../character/Simon.h"
class Axe :
	public CGameObject
{
	CGameObject* owner;
	float OrginalY;
	bool isfinish;
public:
	Axe(CGameObject * owner = NULL);
	~Axe();
	void UpdatePositionRelateToObject(DWORD dt);
	void StartAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void reset();
	// Inherited via CGameObject
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

