#include "CBratizer.h"
#include "../sample/Const_Value.h"

CBratizer::CBratizer(double scalerate)
{

	string source[] = {
	"content\\tilemap\\bratizer_ani.txt"
	};
	LoadResourceHelper::Loadspritefromfile("content\\tilemap\\bratizer_sprites.txt", ID_TEX_BRATIZER);
	LoadResourceHelper::Loadanimationfromfile(source, 1, this);
	this->scale_rate = scalerate;
	this->AddAnimation(602);
	this->state = BRATIZER_STATE_ACTIVE;
}

void CBratizer::Render()
{
	if (state == BRATIZER_STATE_ACTIVE)
		animations[0]->Render(x, y, 255, scale_rate);
	RenderBoundingBox();
}

void CBratizer::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	x_p = (BRATIZER_BBOX_WIDTH - BRATIZER_BBOX_WIDTH * scale_rate) / 2;
	y_p = (BRATIZER_BBOX_HEIGHT - BRATIZER_BBOX_HEIGHT * scale_rate) / 2;
	l = x + x_p;
	t = y + y_p;

	r = l + BRATIZER_BBOX_WIDTH * scale_rate;
	b = t + BRATIZER_BBOX_HEIGHT * scale_rate;
}
