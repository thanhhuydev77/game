#include "Invisibleobject.h"
#include"../utility/LoadResourceHelper.h"
#include "../sample/Textures.h"
#include "../sample/Const_Value.h"

CInvisibleObject::CInvisibleObject()
{
}

void CInvisibleObject::Render()
{
	RenderBoundingBox();
}

void CInvisibleObject::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + boxwidth;
	b = t + boxheight;
}

