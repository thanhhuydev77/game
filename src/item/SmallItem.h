#pragma once
#include "../sample/GameObject.h"
#include "../sample/Textures.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Const_Value.h"
#include "../character/Simon.h"
class SmallItem :
	public CGameObject
{
	DWORD appear_start;
	int Type;
public:
	SmallItem();
	void setType(int type) { Type = type; }
	int getType() { return Type; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	
};

