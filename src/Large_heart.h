#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "LoadResourceHelper.h"
#include "Const_Value.h"
#include "Simon.h"
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

