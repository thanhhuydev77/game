#pragma once
#include <string>
#include "Map.h"
#include "GameObject.h"
#include "Simon.h"
using namespace std;

class Gamemap
{
	Map1 * mmap;
	
public:
	Gamemap();
	void loadmap(string path, int idtex, int screenheight, int screenwidth);
	vector<LPGAMEOBJECT> getBrickobjects();
	vector<LPGAMEOBJECT> getBratizerobjects();
	vector<LPGAMEOBJECT> getItemobjects();
	vector<LPGAMEOBJECT> getallobjects();
	double getscalerate();
	int getmapwidth();
	void Render();
	~Gamemap();
};

