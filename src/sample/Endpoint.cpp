#include "Endpoint.h"

void Endpoint::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + ENDPOINT_BBOX_WIDTH;
	bottom = y + ENDPOINT_BBOX_HEIGHT;
}

void Endpoint::Render()
{
	RenderBoundingBox();
}


