#pragma once
#include "SceneExample.h"
#include <Windows.h>
class SceneManager
{
	static SceneManager *	_instancemanager;
	SceneManager();
	Scene *					_currentScene;

public:
	static SceneManager *	getInstance();
	Scene *					GetCurrentScene();
	void					Update(DWORD dt);
	void					ReplaceScene(Scene *scene);
};

