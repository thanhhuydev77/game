#pragma once
#include <vector>
#include "tileset.h"
#include "../item/CBratizer.h"
#include "Brick.h"
#include "../utility/MathHelper.h"
#include "../character/Simon.h"
#include "../item/Large_heart.h"
#include "../item/Whip_PowerUp.h"
#include "../item/SwordItem.h"
class Map
{
private:
	struct saveobject
	{
		int id;
		int iditem;
		int left;
		int top;
	};
	vector<saveobject> arrobjects;
	TileSet *ts;
	CInvisibleBrick *br;
	CBratizer *bra;
	CGameObject *Largeh;
	std::vector<int> *mapsprite;
	int mawidth;
	int maheight;
	int tilewidth;
	int tileheight;
	int offset;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> Brickobjects;
	vector<LPGAMEOBJECT> Bratizerobjects;
	vector<LPGAMEOBJECT> itemsobjects;
public:
	Map();
	vector<LPGAMEOBJECT> getallObject();
	vector<LPGAMEOBJECT> getBricksObject();
	vector<LPGAMEOBJECT> getBratizersObject();
	vector<LPGAMEOBJECT> getItemsObject();
	void loaditems();
	void loadbricks(int top, int left, int width, int height);
	Map (string filePath,int idtex);
	Map* GetMap();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	void Draw();
	~Map();
};

