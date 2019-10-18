#include "CBratizer.h"
#include "../sample/Const_Value.h"


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

CBratizer::CBratizer(double scalerate)
{
	LPANIMATION ani;
	CTextures * textures = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texbratizer = textures->Get(ID_TEX_BRATIZER);
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	sprites->Add(20111, 0, 0, 32, 64, texbratizer);
	sprites->Add(20112, 32, 0, 64, 64, texbratizer);
	ani = new CAnimation(70);		// brick
	ani->Add(20111);
	ani->Add(20112);
	animations->Add(602, ani);
	this->scale_rate = scalerate;
	this->AddAnimation(602);
	this->state = BRATIZER_STATE_ACTIVE;
}

