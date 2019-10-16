#include "Whip_PowerUp.h"



void Whip_PowerUp::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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

void Whip_PowerUp::Render()
{
	this->Render(1);
}

void Whip_PowerUp::Render(double scalerate)
{
	if (state ==ITEM_STATE_ACTIVE)
		animations[0]->Render(x, y, 255, scalerate, scalerate);
}

void Whip_PowerUp::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + WHIP_POWER_UP_BBOX_WIDTH;
	b = y + WHIP_POWER_UP_BBOX_HEIGHT;

}

Whip_PowerUp::Whip_PowerUp(double scalerate)
{
	LoadResourceHelper::Loadspritefromfile("content\\items\\Whip_PowerUp.txt", ID_TEX_WHIP_POWER_UP);
	string source[] = {
	"content\\items\\Whip_PowerUp_ani.txt"
	};
	LoadResourceHelper::Loadanimationfromfile(source, 1, this);
	this->Scale_Rate = scalerate;
	this->state = ITEM_STATE_UNACTIVE;
}
