#pragma once
#include "../Scene/SceneExample.h"
#include "../character/Simon.h"
#include "../Scene/SceneManager.h"
#include "../sample/Sound.h"
#include "../sample/debug.h"
#include "../sample/Game.h"
#include "../sample/GameObject.h"
#include "../sample/Textures.h"
#include "../camera/Camera.h"
#include "../Scene/SceneGame.h"
class SceneIntro :public Scene
{
	
	Camera *mCamera;
	CGame *games;
	Simon *simon;
	CInvisibleObject* inbrick;
	vector<LPGAMEOBJECT> object;
	DWORD timewait = 0;

public:
	SceneIntro();
	~SceneIntro();
	vector<LPGAMEOBJECT> listeffect;
	// Inherited via Scene
	virtual void Update(DWORD dt) override;
	virtual void LoadContent(int map) override;
	virtual void Draw() override;
	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void KeyState(BYTE *states);
};

