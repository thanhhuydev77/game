#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "../sample/debug.h"
#include "../sample/Game.h"
#include "../sample/GameObject.h"
#include "../sample/Textures.h"
#include "../utility/LoadResourceHelper.h"
#include "../map/Invisibleobject.h"
#include "../character/Simon.h"
#include "../sample/Const_Value.h"
#include "../weapon/Whip.h"
#include "../weapon/Sword.h"
#include "../map/Map.h"
#include "../Scene/SceneExample.h"
#include "../Scene/SceneManager.h"
#include "../camera/Camera.h"
#include "Scene2.h"
using namespace std;

class SceneGame : public Scene
{
private:
	Camera *mCamera;
	Sword *sword;
	CGame *games;
	Simon *simon;
	Whip  *whip;
	Map * mmap;
	int mapwidth;
	CInvisibleObject* typestairstart ;
	vector<LPGAMEOBJECT> objects;  //all object
	vector<LPGAMEOBJECT> BratizerObjects; //all bratizer
	vector<LPGAMEOBJECT> coObjects;//all object except simon
	vector<LPGAMEOBJECT> ItemObjects; //all item object
	vector<LPGAMEOBJECT> BrickObjects; // all brick 
	vector<LPGAMEOBJECT> BrickandpointObjects; // all brick and point
	vector<LPGAMEOBJECT> BratizerandItemObjects; //all bratizers and items
	vector<LPGAMEOBJECT> allStairpoint; // all stair point
	
public:
	SceneGame();
	void loadmap(string path, int idtex);
	vector<LPGAMEOBJECT> getallHidenObjects();
	vector<LPGAMEOBJECT> getBratizerobjects();
	vector<LPGAMEOBJECT> getItemobjects();
	vector<LPGAMEOBJECT> getallobjects();
	vector<LPGAMEOBJECT> getallBrickandpointObjects();
	vector<LPGAMEOBJECT> getallallStairpoint();
	int getmapwidth();
	void RenderBackground();
	~SceneGame();

	// Inherited via SceneExample
	virtual void Update(DWORD dt) override;
	virtual void LoadContent(string mapname, int idmap) override;
	virtual void Draw() override;
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void KeyState(BYTE * states);
};

