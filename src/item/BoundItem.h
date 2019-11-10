#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Const_Value.h"
#include "../sample/textures.h"
class BoundItem :
	public CGameObject
{
	int Type;
	bool disappearing;
	DWORD disappear_start;
	CGameObject *subItem;
public:
	BoundItem();
	void setType(int type) { Type = type; }
	int getType() { return Type; }
	void setSubItem(CGameObject *item) { subItem = item; }
	virtual void Render();
	void start_disappear();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	
};

