#include "LoadResourceHelper.h"
#include<fstream>
#include"textures.h"
#include <string>
LoadResourceHelper::LoadResourceHelper()
{
}

void LoadResourceHelper::Loadspritefromfile(string arrsource, int texnumber)
{
	int idsprite, left, top, right, bottom;
	//string arrsource[] = { "characters\\player\\player_sprites.txt" };
	ifstream infile;
	CSprites * sprites = CSprites::GetInstance();
	CTextures * textures = CTextures::GetInstance();

	LPDIRECT3DTEXTURE9 tex = textures->Get(texnumber);
		infile.open(arrsource);
		if (!infile)
			return;
		while (!infile.eof())
		{
			infile >> idsprite >> left >> top >> right >> bottom;
			sprites->Add(idsprite, left, top, right, bottom, tex);
		}
}

void LoadResourceHelper::Loadanimationfromfile(string arrsource[],int numofsource,CGameObject *object)
{
	
	int idani, time, idsprite;
	string all;
	ifstream infile;
	CSprites * sprites = CSprites::GetInstance();
	CAnimations *anis =CAnimations::GetInstance();
	LPANIMATION ani;
	for (int i = 0; i < numofsource; i++)
	{
		idani = 0;
		infile.open(arrsource[i]);
		while (!infile.eof())
		{

			infile >> idani;
			ani = new CAnimation(100);
			while (!infile.eof())
			{
				infile >> idsprite >> time;
				ani->Add(idsprite, time);
			}
			anis->Add(idani,ani);

			object->AddAnimation(idani);
			
		}
		//infile.clear();
		infile.close();
	}
}

void LoadResourceHelper::loadtileset()
{
}

LoadResourceHelper ::~LoadResourceHelper()
{
}
