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

double Map::getscalerate()
{
	return scale_rate;
}

Map::Map(string filePath, int idtex, int width, int height)
{


	this->screenwidth = width;
	this->screenheight = height;
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
	while (!infile.eof())
	{
		infile >> trashname >> mapname >> trashname >> tileWidth >> trashname >> tileHeight >> trashname >> imagesource >> imageWidth >> imageHeight >> trashname >> mawidth >> trashname >> maheight >> numobjecthasbrick;
		this->mawidth = mawidth;
		this->maheight = maheight;
		this->tilewidth = tileWidth;
		this->tileheight = tileHeight;
		this->offset = idtex * 100;
		for (int n = 0; n < numobjecthasbrick; n++)
		{
			int k;
			infile >> k;
			tilehasbrick.push_back(k);
		}
		ts = new TileSet(mapname, tileWidth, tileHeight, imagesource, imageWidth, imageHeight);
		ts->LoadTileSet(idtex, offset);

		infile >> numobject;
		for (int i = 0; i < numobject; i++)
		{
			{
				int id, left, top;
				infile >> id >> left >> top;
				saveobject obj{ id,left,top };
				arrobjects.push_back(obj);
			}
		}
		while(!infile.eof())
		{
			int mapindex;
			infile >> mapindex;
			mapsprite->push_back(mapindex);
		}
		
	}
	infile.close();

	scale_rate = (screenheight*1.0) / ((maheight)*GetTileHeight());
	addobjects();
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
	return mawidth * tilewidth*scale_rate;
}

int Map::GetHeight()
{
	return maheight * tileheight*scale_rate;
}

int Map::GetTileWidth()
{
	return ts->GetTileWidth();
}

int Map::GetTileHeight()
{
	return ts->GetTileHeight();
}

void Map::addobjects()
{
	for (int i = 0; i < arrobjects.size(); i++)
	{
		if (arrobjects[i].id == 1)
			bra = new CBratizer(scale_rate);
		bra->SetPosition(arrobjects[i].left, arrobjects[i].top);
		Bratizerobjects.push_back(bra);
		objects.push_back(bra);
		if (i == 0 || i == 2)
			Largeh = new Large_heart(scale_rate);
		else if (i == 1 || i == 3)
			Largeh = new Whip_PowerUp(scale_rate);
		else
			Largeh = new SwordItem(scale_rate);
		Largeh->SetPosition(arrobjects[i].left, arrobjects[i].top);
		itemsobjects.push_back(Largeh);
		objects.push_back(Largeh);
	}
}

void Map::Draw()
{
	//ve len man hinh theo ma tran trong mapsprite
	int i = 0;
	int t_width = GetTileWidth();
	int t_height = GetTileHeight();
	
	//ve tu trai sang phai, tren xuong duoi
	for (int y = 0; y < maheight; y++)
		for (int x = 0; x < mawidth; x++)
		{
			ts->get((mapsprite->at(i)))->Draw(x*t_width*scale_rate, y*t_height*scale_rate, 255, scale_rate);
			// some tiles has brick inside
			if (ts->getname() == "map1")
			{
				if (MathHelper::isvectorhaselement(tilehasbrick, mapsprite->at(i)))
					// 1 tile has 2 brick,1 brick has 2 small brick
					for (int k = 0; k < 2; k++)
					{
						br = new CBrick(scale_rate);
						br->SetPosition((x*t_width*scale_rate) + k * 32 * scale_rate, y*t_height*scale_rate + 32 * scale_rate);
						Brickobjects.push_back(br);
						objects.push_back(br);
					}
				i++;
			}

		}
	
}

Map::~Map()
{
}
