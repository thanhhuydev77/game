#include "SmallItem.h"

SmallItem::SmallItem()
{
	LoadResourceHelper::Loadspritefromfile("content\\items\\all_item_sprite.txt", ID_TEX_ITEM);
	LoadResourceHelper::Loadanimationfromfile("content\\items\\all_item_ani.txt", this);
	Type = 0;
	OrginalX = x;
	this->state = ITEM_STATE_UNACTIVE;
}

void SmallItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ITEM_STATE_UNACTIVE)
	{
		OrginalX = x;
		appear_start = GetTickCount();
		if(Type == Const_Value::small_item_type::smallheart)
		vx = SMALL_HEART_SPEED_X;
	}
	if (state == ITEM_STATE_ACTIVE)
	{
		if (appear_start == 0)
			appear_start = GetTickCount();
		if (GetTickCount() - appear_start > ITEM_TIME_APPREARENCE)
		{
			state = ITEM_STATE_UNACTIVE;
			return;
		}

		CGameObject::Update(dt);
		if(Type == Const_Value::small_item_type::smallheart)
		vy = ITEM_GRAVITY ;
		else
			vy += ITEM_GRAVITY;

		if (Type == Const_Value::small_item_type::smallheart)
		{
			if (x - OrginalX >= SMALL_HEART_AROUNDX)
			{
				vx = -SMALL_HEART_SPEED_X;
			}
			else
				if (x - OrginalX <= -SMALL_HEART_AROUNDX)
				{
					vx = SMALL_HEART_SPEED_X;
				}

		}
			
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		CalcPotentialCollisions(coObjects, coEvents);
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CInvisibleObject *>(e->obj) && dynamic_cast<CInvisibleObject *>(e->obj)->Gettype() == Const_Value::Brick)
				{
					vx = 0;
					y += min_ty * dy + ny * 0.1f;
					if (ny != 0) vy = 0;
				}
				else if (dynamic_cast<CInvisibleObject *>(e->obj))
				{
					y += vy*dt;
				}
			}
		}
	}
}

void SmallItem::Render()
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
		animations[Type]->Render(x, y, 255);
		RenderBoundingBox();
	}
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
	case 3:
		width = HOLYWATER_BBOX_WIDTH;
		height = HOLYWATER_BBOX_HEIGHT;
		break;
	case 4:
		width = SWORD_BBOX_WIDTH;
		height = SWORD_BBOX_HEIGHT;
		break;
	case 5:
		width = AXE_BBOX_WIDTH;
		height = AXE_BBOX_HEIGHT;
		break;
	case 6:
	case 7:
	case 8:
		width = MONEYBAG_BBOX_WIDTH;
		height = MONEYBAG_BBOX_HEIGHT;
		break;
	case Const_Value::small_item_type::cross:
		width = CROSS_BBOX_WIDTH;
		height = CROSS_BBOX_HEIGHT;
		break;
	case Const_Value::small_item_type::doubleshot:
		width = DOUBLESHOT_BBOX_WIDTH;
		height = DOUBLESHOT_BBOX_HEIGHT;
		break;
	case Const_Value::small_item_type::invisiblepot:
		width = INVISIBLEPOT_BBOX_WIDTH;
		height = INVISIBLEPOT_BBOX_HEIGHT;
		break;
	case Const_Value::small_item_type::stopwatch:
		width =	STOPWATCH_BBOX_WIDTH;
		height = STOPWATCH_BBOX_HEIGHT;
		break;
	case Const_Value::small_item_type::chicken:
		width = CHICKEN_BBOX_WIDTH;
		height = CHICKEN_BBOX_HEIGHT;
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

