#pragma once
#include <vector>
#include "tile.h"
#include "CBratizer.h"
#include "Brick.h"
#include "../character/Simon.h"
#include "../item/Large_heart.h"
#include "../item/Whip_PowerUp.h"
#include "../item/SwordItem.h"
class Map1
{
private:
	TileSet *ts;
	CBrick *br;
	CBratizer *bra;
	CGameObject *Largeh;
	std::vector<int> *mapsprite;
	int mawidth;
	int maheight;
	int tilewidth;
	int tileheight;
	int offset;
	int screenheight;
	int screenwidth;
	double scale_rate;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> Brickobjects;
	vector<LPGAMEOBJECT> Bratizerobjects;
	vector<LPGAMEOBJECT> itemsobjects;
public:
	vector<LPGAMEOBJECT> getallObject();
	vector<LPGAMEOBJECT> getBricksObject();
	vector<LPGAMEOBJECT> getBratizersObject();
	vector<LPGAMEOBJECT> getItemsObject();
	double getscalerate();
	Map1 (string filePath,int idtex, int width, int height);
	Map1* GetMap();
	Map1();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	
	void Draw();
	~Map1();
};

