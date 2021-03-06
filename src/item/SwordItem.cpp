#include "SwordItem.h"

SwordItem::SwordItem()
{
	LoadResourceHelper::Loadspritefromfile("content\\characters\\player\\Sword\\Sword_sprites.txt", ID_TEX_SWORD);
	LoadResourceHelper::Loadanimationfromfile("content\\characters\\player\\Sword\\Sword_ani.txt", this);
	
	this->state = ITEM_STATE_UNACTIVE;
}

void  SwordItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void  SwordItem::Render()
{
	float t, l, r, b;
	GetBoundingBox(l, t, r, b);
	RECT check;
	check.left = l;
	check.top = t;
	check.right = r;
	check.bottom = b;
	if (Camera::getInstance()->checkInCamera(check))
		if (state == ITEM_STATE_ACTIVE)
		{
			animations[0]->Render(x, y, 255);
			RenderBoundingBox();
		}
}

void  SwordItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	
	l = x ;
	t = y ;

	r = l + SWORD_BBOX_WIDTH ;
	b = t + SWORD_BBOX_HEIGHT ;

}


