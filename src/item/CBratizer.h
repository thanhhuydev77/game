#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Const_Value.h"
#include "../sample/textures.h"

class CBratizer :
	public CGameObject
{
	bool disappearing;
	DWORD disappear_start;
public:
	CBratizer();
	virtual void Render();
	void start_disappear();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	
};

