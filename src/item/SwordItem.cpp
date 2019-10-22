#include "SwordItem.h"

SwordItem::SwordItem(double scalerate)
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\Sword\\Sword_sprites.txt", ID_TEX_SWORD);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\Sword\\Sword_ani.txt", this);
	this->scale_rate = scalerate;
	this->state = ITEM_STATE_UNACTIVE;
}

void  SwordItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (state == ITEM_STATE_ACTIVE)
	{
		CGameObject::Update(dt);
		vy += WHIP_POWER_UP_GRAVITY * dt;
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
				if (dynamic_cast<CBrick *>(e->obj))
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

void  SwordItem::Render()
{
	if (state == ITEM_STATE_ACTIVE)
		animations[0]->Render(x, y, 255, scale_rate);
	RenderBoundingBox();
}

void  SwordItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	x_p = (SWORD_BBOX_WIDTH - SWORD_BBOX_WIDTH * scale_rate) / 2;
	y_p = (SWORD_BBOX_HEIGHT - SWORD_BBOX_HEIGHT * scale_rate) / 2;
	l = x + x_p;
	t = y + y_p;

	r = l + SWORD_BBOX_WIDTH * scale_rate;
	b = t + SWORD_BBOX_HEIGHT * scale_rate;

}


