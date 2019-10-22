#include "CBratizer.h"
#include "../sample/Const_Value.h"

CBratizer::CBratizer(double scalerate)
{

	LoadResourceHelper::Loadspritefromfile("content\\tilemap\\bratizer_sprites.txt", ID_TEX_BRATIZER);
	LoadResourceHelper::Loadanimationfromfile("content\\tilemap\\bratizer_ani.txt", this);

	LoadResourceHelper::Loadspritefromfile("content\\effect\\spark_sprites.txt", ID_TEX_SPARK);
	LoadResourceHelper::Loadanimationfromfile("content\\effect\\spark_ani.txt", this);
	this->scale_rate = scalerate;
	this->AddAnimation(602);
	this->state = BRATIZER_STATE_ACTIVE;
}

void CBratizer::Render()
{
	if (state == BRATIZER_STATE_ACTIVE)
	{
		// defaul ani 
		int ani = 0;
		if (disappearing)
			ani = BRATIZER_ANI_DISAPPEAR;
		animations[ani]->Render(x, y, 255, scale_rate);
	}RenderBoundingBox();
}

void CBratizer::start_disappear()
{
	disappearing = true;
	disappear_start = GetTickCount();
}

void CBratizer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (disappearing)
	{
		if (GetTickCount() - disappear_start > 100)
		{
			disappearing = false;
			disappear_start = 0;
			state = BRATIZER_STATE_UNACTIVE;
		}
		else
		{
		}
	}
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
