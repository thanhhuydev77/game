#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../sample/debug.h"
#include "../sample/Game.h"
#include "../sample/GameObject.h"
#include "../sample/Textures.h"
#include "../utility/LoadResourceHelper.h"
#include "../map/Brick.h"
#include "../character/Simon.h"
#include "../sample/Const_Value.h"
#include "../weapon/Whip.h"
#include "../weapon/Sword.h"
#include "Map.h"
#include "../Scene/SceneExample.h"
#include "../Scene/SceneManager.h"
using namespace std;

class Scene1 : public Scene
{
private:
	Sword *sword;
	CGame *games;
	Simon *simon;
	Whip  *whip;
	Map * mmap;
	int mapwidth;

	vector<LPGAMEOBJECT> objects;  //all object
	vector<LPGAMEOBJECT> BratizerObjects; //all bratizer
	vector<LPGAMEOBJECT> coObjects;//all object except simon
	vector<LPGAMEOBJECT> ItemObjects; //all item object
	vector<LPGAMEOBJECT> BrickObjects; // all brick 
	vector<LPGAMEOBJECT> BratizerandItemObjects; //all bratizers and items

	
public:
	Scene1() {};
	void loadmap(string path, int idtex);
	vector<LPGAMEOBJECT> getBrickobjects();
	vector<LPGAMEOBJECT> getBratizerobjects();
	vector<LPGAMEOBJECT> getItemobjects();
	vector<LPGAMEOBJECT> getallobjects();
	int getmapwidth();
	void RenderBackground();
	~Scene1();

	// Inherited via SceneExample
	virtual void Update(DWORD dt) override;
	virtual void LoadContent() override;
	virtual void Draw() override;
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void KeyState(BYTE * states);
};

