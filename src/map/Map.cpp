#include "Map.h"
#include"tileset.h"
#include <fstream>
#include <vector>
#include "Brick.h"

vector<LPGAMEOBJECT> Map1::getallObject()
{
	return objects;
}

vector<LPGAMEOBJECT> Map1::getBricksObject()
{
	return Brickobjects;
}

vector<LPGAMEOBJECT> Map1::getBratizersObject()
{
	return Bratizerobjects;
}

vector<LPGAMEOBJECT> Map1::getItemsObject()
{
	return itemsobjects;
}

double Map1::getscalerate()
{
	return scale_rate;
}

Map1::Map1(string filePath,int idtex,int width, int height)
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
	while (!infile.eof())
	{
		infile >> trashname >> mapname >> trashname >> tileWidth >> trashname >> tileHeight >> trashname >> imagesource >> imageWidth >> imageHeight >> trashname >> mawidth >> trashname >> maheight;
		this->mawidth = mawidth;
		this->maheight = maheight;
		this->tilewidth = tileWidth;
		this->tileheight = tileHeight;
		this->offset = idtex * 100;
		ts = new TileSet(mapname,tileWidth,tileHeight,imagesource,imageWidth,imageHeight);
		ts->LoadTileSet(idtex,offset);
		while (!infile.eof())
		{
			int mapindex;
			infile >> mapindex;
			mapsprite->push_back(mapindex);
			
		}
	}
}

Map1 * Map1::GetMap()
{
	return nullptr;
}

Map1::Map1()
{
}

int Map1::GetWidth()
{
	return mawidth*tilewidth*scale_rate;
}

int Map1::GetHeight()
{
	return maheight*tileheight*scale_rate;
}

int Map1::GetTileWidth()
{
	return ts->GetTileWidth();
}

int Map1::GetTileHeight()
{
	return ts->GetTileHeight();
}

void Map1::Draw()
{
	//ve len man hinh theo ma tran trong mapsprite
	int i = 0;
	int t_width = GetTileWidth();
	int t_height = GetTileHeight();
	 scale_rate = (screenheight*1.0) / ((maheight)*t_height);
	//ve tu trai sang phai, tren xuong duoi
		for (int y = 0;y< maheight; y++)
			for (int x = 0; x < mawidth; x++)
			{
				ts->get((mapsprite->at(i)))->Draw(x*t_width*scale_rate,y*t_height*scale_rate,255,scale_rate);
				// some tiles has brick inside
				if((mapsprite->at(i))>=25 && (mapsprite->at(i)) <= 33)
					// 1 tile has 2 brick,1 brick has 2 small brick
					for (int k = 0; k < 2; k++)
					{
						br = new CBrick(scale_rate);
						br->SetPosition((x*t_width*scale_rate) + k * 32 * scale_rate , y*t_height*scale_rate + 32 * scale_rate );
						Brickobjects.push_back(br);
						objects.push_back(br);
					}
					if ((x == 4 || x == 7 || x == 10|| x==13 || x ==17) && y == 4)
						{
							bra = new CBratizer(scale_rate);
							bra->SetPosition(((x*t_width*scale_rate)+ 3),(y*t_height*scale_rate - 32 * scale_rate -0.5));
							Bratizerobjects.push_back(bra);
							objects.push_back(bra);
							if (x == 4 || x == 10)
								Largeh = new Large_heart(scale_rate);
							else if(x == 7 || x == 13) 
								Largeh = new Whip_PowerUp(scale_rate);
							else
								Largeh = new SwordItem(scale_rate);
							Largeh->SetPosition(((x*t_width*scale_rate) + 3), (y*t_height*scale_rate - 19 * scale_rate - 0.5 ));
							itemsobjects.push_back(Largeh);
							objects.push_back(Largeh);
						}
					i++;
			}
}

Map1::~Map1()
{
}
