#pragma once
#include "../sample/Sprites.h"
#include <string>
#include "../sample/GameObject.h"
class LoadResourceHelper 
{
public:
	LoadResourceHelper();
	//lay tat ca sprite tu 1 file len danh sach sprites
	static void Loadspritefromfile(string arrsource, int texnumber);
	//lay tat ca idanimation vao danh sach animation cua doi tuong object 
	static void Loadanimationfromfile(string arrsource[],int numofsource, CGameObject *object );
	static void loadtileset();
	~LoadResourceHelper();
};

