#pragma once
#include "../sample/GameObject.h"
#include "../sample/Textures.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Const_Value.h"
#include "../character/Simon.h"
class StaticObject :
	public CGameObject
{
	int Type;
	bool opening;
	DWORD disappear_start;

public:
	StaticObject();
	~StaticObject();

	void setType(int type) { Type = type; }
	int getType() { return Type; }
	void start_open();
	// Inherited via CGameObject
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

