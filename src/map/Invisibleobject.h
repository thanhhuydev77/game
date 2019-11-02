#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Const_Value.h"


class CInvisibleObject : public CGameObject
{
	int boxwidth;
	int boxheight;
	int Type;
public:
	CInvisibleObject();
	void Settype(int type) { Type = type; }
	int Gettype() { return Type; }
	void setsize(int width, int height) { this->boxheight = height; this->boxwidth = width; };
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	

};