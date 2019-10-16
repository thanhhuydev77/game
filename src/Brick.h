#pragma once
#include "GameObject.h"
#include "LoadResourceHelper.h"
#include "Const_Value.h"
#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32

class CBrick : public CGameObject
{
	float scale_rate;
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CBrick(float scalerate = 1);
	// Inherited via CGameObject
	virtual void Render(double scale_rate) override;

};