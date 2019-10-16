#pragma once
#include "GameObject.h"
#include "LoadResourceHelper.h"
#include "Const_Value.h"
#include "textures.h"

class CBratizer :
	public CGameObject
{
	LPANIMATION ani;

public:
	
	virtual void Render();
	void Render(double scalerate = 1);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CBratizer();
};

