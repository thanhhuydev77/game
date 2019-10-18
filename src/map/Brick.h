#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../sample/Const_Value.h"


class CBrick : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CBrick(float scalerate = 1);

};