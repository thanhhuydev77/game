#include "Gamemap.h"



Gamemap::Gamemap()
{
}

void Gamemap::loadmap(string path,int idtex)
{
	mmap = new Map(path,idtex);
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
