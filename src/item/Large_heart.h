#pragma once
#include "../sample/GameObject.h"
#include "../sample/Textures.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Const_Value.h"
#include "../character/Simon.h"
class Large_heart :
	public CGameObject
{
	double Scale_Rate;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	void Render(double scalerate = 1);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	Large_heart(double scalerate = 1);
};

