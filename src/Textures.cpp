#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "textures.h"

CTextures * CTextures::__instance = NULL;

CTextures::CTextures()
{

}

CTextures *CTextures::GetInstance()
{
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}

void CTextures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,			
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	textures[id] = texture;

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

LPDIRECT3DTEXTURE9 CTextures::Get(unsigned int i) 
{
	return textures[i];
}

void CTextures::loadcontent()
{
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_MARIO,			L"content\\textures\\mario.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MISC,			L"content\\textures\\Dirt_Block.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY,			L"content\\textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_BBOX,			L"content\\textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 25));
	textures->Add(ID_TEX_SIMON,			L"content\\textures\\simon.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MAP1,			L"content\\textures\\Courtyard.bmp", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BRATIZER,		L"content\\textures\\Brazier.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WHIP,			L"content\\textures\\Whip.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_LARGE_HEART,	L"content\\textures\\Large_Heart.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WHIP_POWER_UP, L"content\\textures\\Whip_Powerup.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SWORD,			L"content\\textures\\Dagger.png", D3DCOLOR_XRGB(255, 255, 255));

}



