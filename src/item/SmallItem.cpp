#include "SmallItem.h"

SmallItem::SmallItem()
{
	LoadResourceHelper::Loadspritefromfile("content\\items\\all_item_sprite.txt", ID_TEX_ITEM);
	LoadResourceHelper::Loadanimationfromfile("content\\items\\all_item_ani.txt", this);
	Type = 0;
	this->state = ITEM_STATE_UNACTIVE;
}

void SmallItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
					y += min_ty * dy + ny * 0.1f;
					if (ny != 0) vy = 0;
				}
			}
		}
	}
}

void SmallItem::Render()
{
	if (state == ITEM_STATE_ACTIVE)
		animations[Type]->Render(x, y, 255);
	RenderBoundingBox();
}

void SmallItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	int width, height;
	switch (Type)
	{
	case 0:
		width = SMALL_HEART_BBOX_WIDTH;
		height = SMALL_HEART_BBOX_HEIGHT;
		break;
	case 1:
		width = LARGE_HEART_BBOX_WIDTH;
		height = LARGE_HEART_BBOX_HEIGHT;
		break;
	case 2:
		width = WHIP_POWER_UP_BBOX_WIDTH;
		height = WHIP_POWER_UP_BBOX_HEIGHT;
		break;
	case 4:
		width = HOLYWATER_BBOX_WIDTH;
		height = HOLYWATER_BBOX_HEIGHT;
		break;
	case 5:
		width = SWORD_BBOX_WIDTH;
		height = SWORD_BBOX_HEIGHT;
		break;
	default:
		width = SMALL_HEART_BBOX_WIDTH;
		height = SMALL_HEART_BBOX_HEIGHT;
	}
	l = x ;
	t = y ;
	r = l + width ;
	b = t + height;

}

