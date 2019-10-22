#include "Brick.h"
#include"../utility/LoadResourceHelper.h"
#include "../sample/Textures.h"
#include "../sample/Const_Value.h"

CBrick::CBrick(float scalerate)
{
	scale_rate = scalerate;
}

void CBrick::Render()
{
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	x_p = (boxwidth - boxwidth * scale_rate) / 2;
	y_p = (boxheight - boxheight * scale_rate) / 2;
	l = x+x_p;
	t = y+y_p;
	r = l + boxwidth*scale_rate;
	b = t + boxheight*scale_rate;
}

