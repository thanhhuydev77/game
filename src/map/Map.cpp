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

void Map::loaditems()
{
	for (int i = 0; i < arrobjects.size(); i++)
	{
		if (arrobjects[i].id == 1)
			bra = new CBratizer(scale_rate);
		bra->SetPosition(arrobjects[i].left, arrobjects[i].top);
		Bratizerobjects.push_back(bra);
		objects.push_back(bra);
		if (arrobjects[i].iditem == 2)
			Largeh = new Large_heart(scale_rate);
		else if (arrobjects[i].iditem == 3)
			Largeh = new Whip_PowerUp(scale_rate);
		else if (arrobjects[i].iditem == 4)
			Largeh = new SwordItem(scale_rate);
		Largeh->SetPosition(arrobjects[i].left, arrobjects[i].top);
		itemsobjects.push_back(Largeh);
		objects.push_back(Largeh);
	}
}

void Map::loadbricks(int top, int left ,int width,int height)
{
	CBrick *brick = new CBrick(1);
	
	brick->SetPosition(top, left);
	brick->setsize(width, height);
	Brickobjects.push_back(brick);
	objects.push_back(brick);
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
	{
		infile >> trashname >> mapname >> trashname >> tileWidth >> trashname >> tileHeight >> trashname >> imagesource >> imageWidth >> imageHeight >> trashname >> mawidth >> trashname >> maheight;// >>numobjecthasbrick;
		this->mawidth = mawidth;
		this->maheight = maheight;
		this->tilewidth = tileWidth;
		this->tileheight = tileHeight;
		this->offset = idtex * 100;
		/*for (int n = 0; n < numobjecthasbrick; n++)
		{
			int k;
			infile >> k;
			tilehasbrick.push_back(k);
		}*/
		ts = new TileSet(mapname, tileWidth, tileHeight, imagesource, imageWidth, imageHeight);
		ts->LoadTileSet(idtex, offset);

		infile >> numobject;
		for (int i = 0; i < numobject; i++)
		{
			{
				int id,iditem, left, top;
				infile >> id>> iditem >> left >> top;
				saveobject obj{ id,iditem,left,top };
				arrobjects.push_back(obj);
			}
		}
		int numofbricks;
		infile >> numofbricks;
		for (int i = 0; i < numofbricks; i++)
		{
			int top, left, width, height;
			infile >> top >> left >> width >> height;
			loadbricks(top, left, width, height);
			
		}
		for (int i = 0; i <maheight*mawidth; i++)
		{
			int mapindex;
			infile >> mapindex;
			mapsprite->push_back(mapindex);
		}
		
	}
	infile.close();

	scale_rate = (screenheight*1.0) / ((maheight)*GetTileHeight());
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


void Map::Draw()
{
	int i = 0;
	int t_width = GetTileWidth();
	int t_height = GetTileHeight();
	//ve len man hinh theo ma tran trong mapsprite
	for (int y = 0; y < maheight; y++)
		for (int x = 0; x < mawidth; x++)
		{
			ts->get((mapsprite->at(i)))->Draw(x*t_width*scale_rate, y*t_height*scale_rate, 255, scale_rate);
			i++;
		}

}

void Map::drawfirst()
{
	int i = 0;
	int t_width = GetTileWidth();
	int t_height = GetTileHeight();

	//ve tu trai sang phai, tren xuong duoi
	for (int y = 0; y < maheight; y++)
		for (int x = 0; x < mawidth; x++)
		{
			ts->get((mapsprite->at(i)))->Draw(x*t_width*scale_rate, y*t_height*scale_rate, 255, scale_rate);
			i++;
			// some tiles has brick inside
			//if (ts->getname() == "map1")
			//{
			//	//if (MathHelper::isvectorhaselement(tilehasbrick, mapsprite->at(i)))
			//	//	// 1 tile has 2 brick,1 brick has 2 small brick
			//	//	for (int k = 0; k < 2; k++)
			//	//	{
			//	//		br = new CBrick(scale_rate);
			//	//		br->SetPosition((x*t_width*scale_rate) + k * 32 * scale_rate,y*t_height*scale_rate +32);
			//	//		Brickobjects.push_back(br);
			//	//		objects.push_back(br);
			//	//	}
			//	
			//}

		}
	

}

Map::~Map()
{
}
