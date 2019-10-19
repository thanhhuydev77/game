#include "Brick.h"
#include"../utility/LoadResourceHelper.h"
#include "../sample/Textures.h"
#include "../sample/Const_Value.h"

CBrick::CBrick(float scalerate)
{
	string source[] = {
	"content\\tilemap\\brick_ani.txt"
	};
	LoadResourceHelper::Loadspritefromfile("content\\tilemap\\brick_sprites.txt", ID_TEX_MISC);
	LoadResourceHelper::Loadanimationfromfile(source, 1, this);
	scale_rate = scalerate;
}

void CBrick::Render()
{
	animations[0]->Render(x, y, 255, scale_rate);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	x_p = (BRICK_BBOX_WIDTH - BRICK_BBOX_WIDTH * scale_rate) / 2;
	y_p = (BRICK_BBOX_HEIGHT - BRICK_BBOX_HEIGHT * scale_rate) / 2;
	l = x+x_p;
	t = y+y_p;
	r = l + BRICK_BBOX_WIDTH*scale_rate;
	b = t + BRICK_BBOX_HEIGHT*scale_rate;
}

