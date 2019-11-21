#pragma once
#include "../sample/GameObject.h"
#include "../map/Invisibleobject.h"
#include "../character/Simon.h"
class Holy_Water :
	public CGameObject
{
	CGameObject* owner;
	float OrginalY;
	bool isfinish;
	bool fallen;
	DWORD disappear_start;
	bool disappearing;
public:
	Holy_Water(CGameObject * owner = NULL);
	~Holy_Water();
	void UpdatePositionRelateToObject(DWORD dt);
	void start_disappear();
	void StartAttack();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void reset();
	// Inherited via CGameObject
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

