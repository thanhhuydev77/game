#include "BoundItem.h"
#include "../sample/Const_Value.h"

BoundItem::BoundItem()
{

	LoadResourceHelper::Loadspritefromfile("content\\tilemap\\bratizer_sprites.txt", ID_TEX_BITEM);
	LoadResourceHelper::Loadanimationfromfile("content\\tilemap\\bratizer_ani.txt", this);


	Type = 0;
	this->AddAnimation(602);
	this->state = BRATIZER_STATE_ACTIVE;
}

void BoundItem::Render()
{
	//bool checkin = false;
	float t, l, r, b;
	GetBoundingBox(l, t, r, b);
	RECT check;
	check.left = l;
	check.top = t;
	check.right = r;
	check.bottom = b;
	if(Camera::getInstance()->checkInCamera(check))
	if (state == BRATIZER_STATE_ACTIVE)
	{
		//checkin = true;
		// defaul ani 
		//int ani = 0;
		// animations 2 is flame
		if (disappearing)
		{
			if (Type == Const_Value::bound_item_type::Bratizer)
			{
				animations[Const_Value::bound_item_type::flame]->Render(x + 7, y + 7, 255);
			}
			else
				if (Type == Const_Value::bound_item_type::candle)
				{
					animations[Const_Value::bound_item_type::flame]->Render(x, y, 255);
				}
		}
		else
		animations[Type]->Render(x, y, 255);
		
	}
	RenderBoundingBox();
	//DebugOut(L"is render :%d",checkin);
}

void BoundItem::start_disappear()
{
	//animations[Const_Value::bound_item_type::flame]->reset();
	disappearing = true;
	disappear_start = GetTickCount();
}

void BoundItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (disappearing)
	{
		if (GetTickCount() - disappear_start > 300)
		{
			disappearing = false;
			disappear_start = 0;
			state = ITEM_STATE_UNACTIVE;
			subItem->SetState(ITEM_STATE_ACTIVE);
		}
	}
}

void BoundItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	int width, height;
	if (!disappearing && state == ITEM_STATE_ACTIVE || ((Type == Const_Value::bound_item_type::Bratizer || Type == Const_Value::bound_item_type::candle) && state == ITEM_STATE_ACTIVE) )
	{
		switch (Type)
		{
		case Const_Value::bound_item_type::Bratizer:
			width = BRATIZER_BBOX_WIDTH;
			height = BRATIZER_BBOX_HEIGHT;
			break;
		case Const_Value::bound_item_type::candle:
			width = CANDLE_BBOX_WIDTH;
			height = CANDLE_BBOX_HEIGHT;
			break;

		case Const_Value::bound_item_type::breakableBrick:

			width = BRICK_BBOX_WIDTH;
			height = BRICK_BBOX_HEIGHT;


			break;
		case Const_Value::bound_item_type::BreakableBlock:
			if (state == ITEM_STATE_ACTIVE)
			{
				width = BLOCK_BBOX_WIDTH;
				height = BLOCK_BBOX_HEIGHT;
			}
			else
			{
				l = 0;
				t = 0;
				r = 0;
				b = 0;
				return;
			}
			break;
		default:
			width = 0;
			height = 0;
			break;
		}
		l = x;
		t = y;

		r = l + width;
		b = t + height;
	}
	else
	{
		l = 0;
		t = 0;
		r = 0;
		b = 0;
	}
}
