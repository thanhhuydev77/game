#include "StaticObject.h"



StaticObject::StaticObject()
{
	LoadResourceHelper::Loadspritefromfile("content\\items\\Static_obj_sprite.txt", ID_TEX_STATIC_OBJ);
	LoadResourceHelper::Loadanimationfromfile("content\\items\\Static_obj_ani.txt", this);
	Type = 0;
	this->state = ITEM_STATE_UNACTIVE;
}


StaticObject::~StaticObject()
{
}

void StaticObject::start_open()
{
	opening = true;
	disappear_start = GetTickCount();
	state = ITEM_STATE_ACTIVE;
}

void StaticObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (opening)
	{
		if (GetTickCount() - disappear_start > DOOR_OPEN_ANI_TIME)
		{
			opening = false;
			disappear_start = 0;
			state = ITEM_STATE_UNACTIVE;
		}
	}
}

void StaticObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	int width, height;
	
	switch (Type)
	{
	case 0:
		if (!opening)
		{

			width = DOOR_BBOX_WIDTH;
			height = DOOR_BBOX_HEIGHT;
		}
		else
		{
			width = 0;
			height = 0;
		}
		break;
	
	default:
		width = 0;
		height = 0;
	}
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}

void StaticObject::Render()
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
			//RenderBoundingBox();
		}
		else
		{
			animations[Type]->GetFrame(0)->GetSprite()->Draw(x, y, 255);
			RenderBoundingBox();
		}
}
