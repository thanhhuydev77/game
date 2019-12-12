#include "Board.h"



Board::Board()
{
	LoadResourceHelper::Loadspritefromfile("content\\Font\\Board_sprite.txt", ID_TEX_BOARD);
	LoadResourceHelper::Loadanimationfromfile("content\\Font\\Board_ani.txt", this);
	x = 0;
	y = 0;
}


Board::~Board()
{
}

void Board::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}

void Board::Render()
{
	animations[0]->GetFrame(0)->GetSprite()->Draw(Camera::getInstance()->Getx(),y,255);
}
