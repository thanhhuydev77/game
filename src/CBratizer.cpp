#include "CBratizer.h"
#include "Const_Value.h"


void CBratizer::Render()
{
	this->Render(1);
}

void CBratizer::Render(double scalerate)
{
	if(state == BRATIZER_STATE_ACTIVE)
	animations[0]->Render(x, y, 255, scalerate, scalerate);
}

void CBratizer::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + BRATIZER_BBOX_WIDTH;
	b = y + BRATIZER_BBOX_HEIGHT;
}

CBratizer::CBratizer()
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
	this->AddAnimation(602);
	this->state = BRATIZER_STATE_ACTIVE;
}

