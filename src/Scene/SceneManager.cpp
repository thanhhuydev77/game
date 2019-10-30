#include "SceneManager.h"


SceneManager * SceneManager::_instancemanager = NULL;
SceneManager * SceneManager::getInstance()
{
	if (_instancemanager == NULL) _instancemanager = new SceneManager();
	return _instancemanager;
}

Scene * SceneManager::GetCurrentScene()
{
	return _currentScene;
}

void SceneManager::Update(DWORD dt)
{
	_currentScene->Update(dt);
}
SceneManager::SceneManager()
{
	
	_currentScene = nullptr;
}
void SceneManager::ReplaceScene(Scene * scene)
{
	delete _currentScene;
	_currentScene = scene;
}

