#include "Brick.h"
#include"../utility/LoadResourceHelper.h"
#include "../sample/Textures.h"
#include "../sample/Const_Value.h"

void CBrick::Render()
{
	animations[0]->Render(x, y,255,scale_rate,scale_rate);
	//RenderBoundingBox();
}
void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
CBrick::CBrick(float scalerate)
{
	LPANIMATION ani;
	CTextures * textures = CTextures::GetInstance();
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	sprites->Add(20001, 0, 0,32,32, texMisc);
	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	scale_rate = scalerate;
	animations->Add(601, ani);
	this->AddAnimation(601);
		
}

void CBrick::Render(double scale_rate)
{
	animations[0]->Render(x, y, 255, scale_rate, scale_rate);
}
