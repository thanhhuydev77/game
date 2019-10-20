#include "Gamemap.h"



Gamemap::Gamemap()
{
}

void Gamemap::loadmap(string path,int idtex,int screenheight,int screenwidth)
{
	mmap = new Map(path,idtex,screenwidth,screenheight);
	mmap->drawfirst();
}

vector<LPGAMEOBJECT> Gamemap::getBrickobjects()
{
	return mmap->getBricksObject();
}

vector<LPGAMEOBJECT> Gamemap::getBratizerobjects()
{
	return mmap->getBratizersObject();
}

vector<LPGAMEOBJECT> Gamemap::getItemobjects()
{
	return mmap->getItemsObject();
}

vector<LPGAMEOBJECT> Gamemap::getallobjects()
{
	return mmap->getallObject();
}

double Gamemap::getscalerate()
{
	return mmap->getscalerate();
}

int Gamemap::getmapwidth()
{
	return mmap->GetWidth();
}

void Gamemap::Render()
{
	mmap->Draw();
}

Gamemap::~Gamemap()
{
}
