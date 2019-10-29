#include "Brick.h"
#include"../utility/LoadResourceHelper.h"
#include "../sample/Textures.h"
#include "../sample/Const_Value.h"

CInvisibleBrick::CInvisibleBrick()
{
}

void CInvisibleBrick::Render()
{
	RenderBoundingBox();
}

void CInvisibleBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = l + boxwidth;
	b = t + boxheight;
}

