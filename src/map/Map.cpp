#include "Map.h"
#include"tileset.h"
#include <fstream>
#include <vector>
#include "Brick.h"

vector<LPGAMEOBJECT> Map::getallObject()
{
	return objects;
}

vector<LPGAMEOBJECT> Map::getBricksObject()
{
	return Brickobjects;
}

vector<LPGAMEOBJECT> Map::getBratizersObject()
{
	return Bratizerobjects;
}

vector<LPGAMEOBJECT> Map::getItemsObject()
{
	return itemsobjects;
}

void Map::loaditems()
{
	for (int i = 0; i < arrobjects.size(); i++)
	{
		if (arrobjects[i].id == 1)
			bra = new CBratizer();
		bra->SetPosition(arrobjects[i].left, arrobjects[i].top+ OFFSET_Y);
		Bratizerobjects.push_back(bra);
		objects.push_back(bra);
		if (arrobjects[i].iditem == 2)
			Largeh = new Large_heart();
		else if (arrobjects[i].iditem == 3)
			Largeh = new Whip_PowerUp();
		else if (arrobjects[i].iditem == 4)
			Largeh = new SwordItem();
		Largeh->SetPosition(arrobjects[i].left, arrobjects[i].top+ OFFSET_Y);
		itemsobjects.push_back(Largeh);
		objects.push_back(Largeh);
	}
}

void Map::loadinvisibleobjects(int id,int top, int left, int width, int height)
{
	switch (id)
	{
	case 0:
		CInvisibleBrick *inbrick;
		inbrick = new CInvisibleBrick();
		inbrick->setsize(width, height);
		inbrick->SetPosition(top, left+OFFSET_Y);
		Brickobjects.push_back(inbrick);
		objects.push_back(inbrick);
		break;
	case 2:
		Endpoint *inendpoint = new Endpoint();
		inendpoint->SetPosition(top, left+OFFSET_Y);
		Brickobjects.push_back(inendpoint);
		objects.push_back(inendpoint);
		break;
	}
	
	
	
}

Map::Map(string filePath, int idtex)
{
	mapsprite = new vector<int>();
	ifstream infile;
	infile.open(filePath);
	if (!infile)
		return;
	string trashname;
	string mapname;
	int tileWidth;
	int tileHeight;
	string imagesource;
	int imageWidth;
	int imageHeight;
	int mawidth;
	int maheight;
	int numobjecthasbrick;
	int numobject;
	{
		infile >> trashname >> mapname >> trashname >> tileWidth >> trashname >> tileHeight >> trashname >> imagesource >> imageWidth >> imageHeight >> trashname >> mawidth >> trashname >> maheight;// >>numobjecthasbrick;
		this->mawidth = mawidth;
		this->maheight = maheight;
		this->tilewidth = tileWidth;
		this->tileheight = tileHeight;
		this->offset = idtex * 100;
		//load tileset
		ts = new TileSet(mapname, tileWidth, tileHeight, imagesource, imageWidth, imageHeight);
		ts->LoadTileSet(idtex, offset);
		//load visible object
		infile >> numobject;
		for (int i = 0; i < numobject; i++)
		{
			{
				int id, iditem, left, top;
				infile >> id >> iditem >> left >> top;
				saveobject obj{ id,iditem,left,top };
				arrobjects.push_back(obj);
			}
		}
		int numofobjects;
		//load invisible object
		infile >> numofobjects;
		for (int i = 0; i < numofobjects; i++)
		{
			int id,top, left, width, height;
			infile >>id>> top >> left >> width >> height;
			loadinvisibleobjects(id,top, left, width, height);

		}
		for (int i = 0; i < maheight*mawidth; i++)
		{
			int mapindex;
			infile >> mapindex;
			mapsprite->push_back(mapindex);
		}

	}
	infile.close();
	loaditems();
}

Map * Map::GetMap()
{
	return nullptr;
}

Map::Map()
{
}

int Map::GetWidth()
{
	return mawidth * tilewidth;
}

int Map::GetHeight()
{
	return maheight * tileheight;
}

int Map::GetTileWidth()
{
	return ts->GetTileWidth();
}

int Map::GetTileHeight()
{
	return ts->GetTileHeight();
}


void Map::Draw()
{
	int i = 0;
	
	int t_width = GetTileWidth();
	int t_height = GetTileHeight();
	//ve len man hinh theo ma tran trong mapsprite
	for (int y = 0; y < maheight; y++)
		for (int x = 0; x < mawidth; x++)
		{
			ts->get((mapsprite->at(i)))->Draw(x*t_width, y*t_height+OFFSET_Y, 255);
			i++;
		}

}

Map::~Map()
{
}
