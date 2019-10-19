#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Const_Value.h"
#include "../sample/textures.h"

class CBratizer :
	public CGameObject
{
public:
	CBratizer(double scalerate = 1);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	
};

