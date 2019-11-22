#include "Effect.h"

Effect::Effect(int type, float x, float y, float vx, float vy)
{
	LoadResourceHelper::Loadspritefromfile("content\\effect\\all_effect_sprite.txt", ID_TEX_EFFECT);
	LoadResourceHelper::Loadanimationfromfile("content\\effect\\all_effect_ani.txt", this);
	this->Type = type;
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	timestart = GetTickCount();
	finish = false;
}

Effect::~Effect()
{
}

void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (!finish)
	{
		if(Type == Const_Value::effect_type::broken || Type == Const_Value::effect_type::water)
		vy += EFFECT_GRAVITY * dt;
		if (GetTickCount() - timestart > TIME_ACTIVE)
		{
			finish = true;
			return;
		}
		x += dx;
		y += dy;
	}
	
}

void Effect::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = 0;
	right = 0;
	top = 0;
	bottom = 0;
}

void Effect::Render()
{
	if(!finish)
	animations[Type]->Render(x, y, 255);
}
