#include "Whip_PowerUp.h"

Whip_PowerUp::Whip_PowerUp()
{
	LoadResourceHelper::Loadspritefromfile("content\\items\\Whip_PowerUp.txt", ID_TEX_WHIP_POWER_UP);
	LoadResourceHelper::Loadanimationfromfile("content\\items\\Whip_PowerUp_ani.txt", this);

	this->state = ITEM_STATE_UNACTIVE;
}

void Whip_PowerUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (state == ITEM_STATE_ACTIVE)
	{
		CGameObject::Update(dt);
		vy += ITEM_GRAVITY * dt;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		if (coEvents.size() == 0)
		{
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CInvisibleObject *>(e->obj))
				{
					// block 
							// nx*0.4f : need to push out a bit to avoid overlapping next frame
					y += min_ty * dy + ny * 0.1f;


					if (ny != 0) vy = 0;
				}
			}
		}
	}
}

void Whip_PowerUp::Render()
{
	if (state == ITEM_STATE_ACTIVE)
		animations[0]->Render(x, y, 255);
	RenderBoundingBox();
}

void Whip_PowerUp::GetBoundingBox(float & l, float & t, float & r, float & b)
{

	l = x;
	t = y;

	r = l + WHIP_POWER_UP_BBOX_WIDTH;
	b = t + WHIP_POWER_UP_BBOX_HEIGHT;

}


