#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <string>
#include "../sample/Sprites.h"
using namespace std;

class TileSet
{
	
	string name;
	int tileWidth;
	int tileHeight;
	string imagesource;
	int mawidth;
	int maheight;
	int imageWidth;
	int imageHeight;
	bool hasobject;
public:
	TileSet();
	TileSet(string name,int tilewidth,int tileheight,string imagesource,int imagewidth,int imageheight);
	int GetTileWidth() const { return tileWidth; }
	int GetTileHeight() const { return tileHeight; }
	int Getmawidth() const { return mawidth; }
	string getname() { return name; }
	int Getmaheight() const { return maheight; }
	vector<CSprite*> tiles;
	CSprite* get(int index);
	void LoadTileSet( int idtex, int offset);
};