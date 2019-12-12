#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <random>
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
#include "../enemies/Ghost.h"
#include "../enemies/Panther.h"
#include "../enemies/Bat.h"
#include "../weapon/Fireball.h"
#include "../enemies/Fishmen.h"
#include "../weapon/Axe.h"
#include "../weapon/Holy_Water.h"
#include "../effect/Effect.h"
#include "../boss/Boss.h"
#include "../sample/Board.h"
#include "../sample/Sound.h"
using namespace std;

class SceneGame : public Scene
{
private:
	Camera *mCamera;
	Sword *sword;
	CGame *games;
	Simon *simon;
	Whip  *whip;
	Board *board;
	Boss *boss;
	SmallItem *smb;
	Axe *axe;
	Holy_Water *holywater;
	Map * mmap;
	//Ghost *ghost;
	int mapwidth;
	bool wait_to_create_Ghost;
	int num_of_ghost = 0;
	int groundY;
	DWORD timecreatGhost;
	int CountEnemyPanther;
	int CountEnemyGhost;
	int CountEnemyFishmen;
	bool isAllowCreateBat;
	vector<int> currentGrids;
	DWORD lasttimedamage;
	DWORD TimeCreateFishmen;
	DWORD TimeWaitCreateFishmen;
	bool changemap;
	DWORD TimeCreateBat; 
	DWORD TimeWaitCreateBat; 
	int CountEnemyBat;
	CInvisibleObject* typestairstart ;
	vector<LPGAMEOBJECT> allfireball;  //all object
	vector<LPGAMEOBJECT> listeffect;
	vector<LPGAMEOBJECT> objects;  //all object
	vector<LPGAMEOBJECT> BoundObjects; //all bratizer
	vector<LPGAMEOBJECT> coObjects;//all object except simon
	vector<LPGAMEOBJECT> ItemObjects; //all item object
	vector<LPGAMEOBJECT> BrickObjects; // all brick 
	vector<LPGAMEOBJECT> BrickandpointObjects; // all brick and point
	vector<LPGAMEOBJECT> BoundandItemObjects; //all bratizers and items
	vector<LPGAMEOBJECT> allStairpoint; // all stair point
	vector<LPGAMEOBJECT> allStaticObject;
	vector<LPGAMEOBJECT> allEnemies; 

	
public:
	SceneGame();
	void loadmap(int map);
	vector<LPGAMEOBJECT> getallHidenObjects();
	vector<LPGAMEOBJECT> getBoundobjects();
	vector<LPGAMEOBJECT> getItemobjects();
	vector<LPGAMEOBJECT> getallobjects();
	vector<LPGAMEOBJECT> getallBrickandpointObjects();
	vector<LPGAMEOBJECT> getallallStairpoint();
	vector<LPGAMEOBJECT> getallStaticObject();
	int getmapwidth();
	int currentMap = 0;
	void resetlist();
	void RenderBackground();
	~SceneGame();
	void collisionweapond();
	// Inherited via SceneExample
	virtual void Update(DWORD dt) override;
	virtual void LoadContent(int map) override;
	virtual void Draw() override;
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void KeyState(BYTE * states);
};

