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
	if (state == BRATIZER_STATE_ACTIVE)
	{
		// defaul ani 
		//int ani = 0;
		// animations 2 is flame
		if (disappearing)
			if(Type == Const_Value::bound_item_type::Bratizer)
			animations[2]->Render(x+7, y+7, 255);
			else
				animations[2]->Render(x , y, 255);
		else
		animations[Type]->Render(x, y, 255);
		RenderBoundingBox();
	}
}

void BoundItem::start_disappear()
{
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
			state = BRATIZER_STATE_UNACTIVE;
			subItem->SetState(ITEM_STATE_ACTIVE);
		}
	}
}

void BoundItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	int width, height;
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
	default:
		width = BRATIZER_BBOX_WIDTH;
		height = BRATIZER_BBOX_HEIGHT;
		break;
	}
	l = x ;
	t = y ;

	r = l + width ;
	b = t + height ;
}
