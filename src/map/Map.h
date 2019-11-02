#pragma once
#include <vector>
#include "tileset.h"
#include "../item/CBratizer.h"
#include "Invisibleobject.h"
#include "../sample/Const_Value.h"
#include "../utility/MathHelper.h"
#include "../character/Simon.h"
#include "../item/Large_heart.h"
#include "../item/Whip_PowerUp.h"
#include "../item/SwordItem.h"
#include "../sample/Endpoint.h"
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
	CInvisibleObject *inobj;
	CBratizer *bra;
	CGameObject *Largeh;
	std::vector<int> *mapsprite;
	int mawidth;
	int maheight;
	int tilewidth;
	int tileheight;
	int offset;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> allHidenObject;
	vector<LPGAMEOBJECT> Bratizerobjects;
	vector<LPGAMEOBJECT> itemsobjects;
	vector<LPGAMEOBJECT> allbrickandpoint;
	vector<LPGAMEOBJECT> allstairpoint;

public:
	Map();
	vector<LPGAMEOBJECT> getallObject();
	vector<LPGAMEOBJECT> getallHidenObject();
	vector<LPGAMEOBJECT> getBratizersObject();
	vector<LPGAMEOBJECT> getItemsObject();
	vector<LPGAMEOBJECT> getallbrickandpoint();
	vector<LPGAMEOBJECT> getallstairpoint();
	void loaditems();
	void loadinvisibleobjects(int id,int top, int left, int width, int height);
	Map (string filePath,int idtex);
	Map* GetMap();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	void Draw();
	~Map();
};

