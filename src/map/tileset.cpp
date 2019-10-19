#include "tileset.h"
#include"../sample/Game.h"
#include<fstream>
#include "../sample/Sprites.h"
#include "../sample/textures.h"




TileSet::TileSet()
{
}

TileSet::TileSet(string name, int tilewidth, int tileheight, string imagesource, int imagewidth, int imageheight)
{
	this->name = name;
	this->tileWidth = tilewidth;
	this->tileHeight = tileheight;
	this->imagesource = imagesource;
	this->imageWidth = imagewidth;
	this->imageHeight = imageheight;
	
}

CSprite *TileSet::get(int index)
{
	//start by 0
	return tiles[index];
}

void TileSet::LoadTileSet(int idtex,int offset)
{
	int idp = 0;
		CTextures * textures = CTextures::GetInstance();	
		LPDIRECT3DTEXTURE9 texmap1 = textures->Get(idtex);
		CSprites *ls = CSprites::GetInstance();

		for (int y = 0; y < imageHeight / tileHeight; y++)  //doc theo y
			for (int x = 0; x < imageWidth/tileWidth; x++)	//doc theo x
			{
				int left = x * tileWidth;
				int top = y * tileHeight;
				int right = left + tileWidth;
				int bottom = top + tileHeight;
				ls->Add(offset+idp, left, top, right, bottom, texmap1);
				tiles.push_back(ls->Get(offset + idp));
				idp++;
			}	
		
}

