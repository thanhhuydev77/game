#include "Map.h"
#include"tileset.h"
#include <fstream>
#include <vector>
#include "Invisibleobject.h"

vector<LPGAMEOBJECT> Map::getallObject()
{
	return objects;
}

vector<LPGAMEOBJECT> Map::getallHidenObject()
{
	return allHidenObject;
}

vector<LPGAMEOBJECT> Map::getBratizersObject()
{
	return Bratizerobjects;
}

vector<LPGAMEOBJECT> Map::getItemsObject()
{
	return itemsobjects;
}

vector<LPGAMEOBJECT> Map::getallbrickandpoint()
{
	return allbrickandpoint;
}

vector<LPGAMEOBJECT> Map::getallstairpoint()
{
	return allstairpoint;
}

vector<LPGAMEOBJECT> Map::getallstaticObject()
{
	return allstaticObject;
}

void Map::loaditems()
{
	for (int i = 0; i < arrobjects.size(); i++)
	{
		bra = new BoundItem();
		bra->setType(arrobjects[i].id);
		bra->SetPosition(arrobjects[i].left, arrobjects[i].top + OFFSET_Y);
		Bratizerobjects.push_back(bra);
		objects.push_back(bra);
		if (bra->getType() == Const_Value::bound_item_type::BreakableBlock || bra->getType() == Const_Value::bound_item_type::breakableBrick)
		{
			allbrickandpoint.push_back(bra);
		}
		smallitem = new SmallItem();
		smallitem->setType(arrobjects[i].iditem);
		smallitem->SetPosition(arrobjects[i].left, arrobjects[i].top + OFFSET_Y);
		itemsobjects.push_back(smallitem);
		objects.push_back(smallitem);
		bra->setSubItem(smallitem);

	}
}

void Map::loadStaticObject(int id, int left, int top)
{
	StaticObject *st_obj;
	st_obj = new StaticObject();
	//st_obj->setDirect(direct);
	st_obj->setType(id);

	st_obj->SetPosition(left, top + OFFSET_Y);
	//allHidenObject.push_back(in_obj);
	allbrickandpoint.push_back(st_obj);
	allstaticObject.push_back(st_obj);
	objects.push_back(st_obj);
}

void Map::loadinvisibleobjects(int id, int direct, int top, int left, int width, int height)
{

	CInvisibleObject *in_obj;
	in_obj = new CInvisibleObject();
	in_obj->setDirect(direct);
	in_obj->Settype(id);
	
	if (id == 0)
		allbrickandpoint.push_back(in_obj);
	else
		allstairpoint.push_back(in_obj);

	in_obj->setsize(width, height);
	in_obj->SetPosition(top, left + OFFSET_Y);
	allHidenObject.push_back(in_obj);
	objects.push_back(in_obj);
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
			int id, direct, top, left, width, height;
			infile >> id >> direct >> top >> left >> width >> height;
			loadinvisibleobjects(id, direct, top, left, width, height);

		}
		int numofstaticobjects;
		infile >> numofstaticobjects;
		for (int i = 0; i < numofstaticobjects; i++)
		{
			int id,left,top;
			infile >> id >> left >> top ;
			loadStaticObject(id,left,top);
		}
		int numarea;
		infile >> numarea;
		for (int i = 0; i < numarea; i++)
		{
			int area;
			infile >> area;
			activearea.push_back(area);
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
	Camera::getInstance()->setactivearea(activearea);
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
	//int num = 0;
	//ve len man hinh theo ma tran trong mapsprite
	for (int y = 0; y < maheight; y++)
		for (int x = 0; x < mawidth; x++)
		{
			float cx = x * t_width;
			float cy = y * t_height + OFFSET_Y;
			RECT locate;
			locate.left = cx;
			locate.top = cy;
			locate.right = cx + t_width;
			locate.bottom = cy + t_height;
				
				
			bool check = Camera::getInstance()->checkInCamera(locate);
			if (check)
			{
				//num++;
				ts->get((mapsprite->at(i)))->Draw(cx, cy, 255);
			}
			i++;
			//DebugOut(L"tile at %d : %d", i, check);
		}
	//DebugOut(L"num : %d", num);
}

Map::~Map()
{
}
