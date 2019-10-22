#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Const_Value.h"


class CBrick : public CGameObject
{
	int boxwidth;
	int boxheight;
public:
	CBrick(float scalerate = 1);
	void setsize(int width, int height) { this->boxheight = height; this->boxwidth = width; };
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	

};