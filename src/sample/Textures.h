#pragma once
#include <unordered_map>
#include <d3dx9.h>
#include "Const_Value.h"
#include "../utility/LoadResourceHelper.h"
using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures * __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public: 
	CTextures();
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	void loadcontent();
	static CTextures * GetInstance();
};