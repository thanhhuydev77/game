#pragma once
#include <Windows.h>
#include <string>
using namespace std;

class Scene
{
public:

	virtual void Update(DWORD dt) = 0;
	virtual void LoadContent(int map) = 0;
	virtual void Draw() = 0;

	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void KeyState(BYTE *states);

};
