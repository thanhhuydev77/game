#include "Large_heart.h"

Large_heart::Large_heart(double scalerate)
{
	LoadResourceHelper::Loadspritefromfile("content\\items\\Large_heart.txt", ID_TEX_LARGE_HEART);
	string source[] = {
	"content\\items\\Large_heart_ani.txt"
	};
	LoadResourceHelper::Loadanimationfromfile(source, 1, this);
	this->scale_rate = scalerate;
	this->state = ITEM_STATE_UNACTIVE;
}

void Large_heart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (state == ITEM_STATE_ACTIVE)
	{
		CGameObject::Update(dt);
		vy += LARGE_HEART_GRAVITY * dt;
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
					y += min_ty * dy + ny * 0.1f;
					if (ny != 0) vy = 0;
				}
			}
		}
	}
}

void Large_heart::Render()
{
	if (state == ITEM_STATE_ACTIVE)
		animations[0]->Render(x, y, 255, scale_rate);
	RenderBoundingBox();
}

void Large_heart::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	x_p = (LARGE_HEART_BBOX_WIDTH - LARGE_HEART_BBOX_WIDTH * scale_rate) / 2;
	y_p = (LARGE_HEART_BBOX_HEIGHT - LARGE_HEART_BBOX_HEIGHT * scale_rate) / 2;
	l = x + x_p;
	t = y + y_p;

	r = l + LARGE_HEART_BBOX_WIDTH * scale_rate;
	b = t + LARGE_HEART_BBOX_HEIGHT * scale_rate;

}

