#pragma once
#include <vector>
#include "tileset.h"
#include "../item/BoundItem.h"
#include "Invisibleobject.h"
#include "../sample/Const_Value.h"
#include "../utility/MathHelper.h"
#include "../character/Simon.h"
#include "../item/SmallItem.h"
#include "../item/Whip_PowerUp.h"
#include "../item/SwordItem.h"
#include "../sample/Endpoint.h"
#include "../camera/Camera.h"
#include "../item/StaticObject.h"
#include "../sample/Grid.h"
class Map
{
private:
	struct saveobject
	{
		int id;
		int iditem;
		int left;
		int top;
		vector<int> grid;
	};
	vector<saveobject> arrobjects;
	TileSet *ts;
	CInvisibleObject *inobj;
	BoundItem *bra;
	SmallItem *smallitem;
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
	vector<LPGAMEOBJECT> allstaticObject;
	vector<int> activearea;
public:
	Map();
	vector<LPGAMEOBJECT> getallObject();
	vector<LPGAMEOBJECT> getallHidenObject();
	vector<LPGAMEOBJECT> getBratizersObject();
	vector<LPGAMEOBJECT> getItemsObject();
	vector<LPGAMEOBJECT> getallbrickandpoint();
	vector<LPGAMEOBJECT> getallstairpoint();
	vector<LPGAMEOBJECT> getallstaticObject();
	void loaditems();
	void loadStaticObject(int id, int top, int left, vector<int> ligrid);
	void loadinvisibleobjects(int id,int direct,int top, int left, int width, int height,vector<int> ligrid);
	Map (string filePath,int idtex);
	Map* GetMap();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	void Draw();
	~Map();
};

