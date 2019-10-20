#pragma once
#include <vector>
#include "tileset.h"
#include "CBratizer.h"
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
		int left;
		int top;
	};
	vector<saveobject> arrobjects;
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
	vector<int> tilehasbrick;
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
	double getscalerate();
	Map (string filePath,int idtex, int width, int height);
	Map* GetMap();
	int GetWidth();
	int GetHeight();
	int GetTileWidth();
	int GetTileHeight();
	void addobjects();
	void Draw();
	~Map();
};

