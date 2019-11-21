#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../sample/GameObject.h"
#include "../sample/Game.h"
#include "../character/Simon.h"
#include"../sample/debug.h"
class Camera
{
	static Camera * _instance;
	int             mWidth,mHeight;
	D3DXVECTOR3     mPosition;
	bool isfollowSimon;
	float camx, camy;
	vector<int> activearea;
	int currentarea = 0;
	bool autotransiting;
	DWORD autotrans_start;
	int des;
	int turn;

public:
	static Camera *getInstance();
	void setactivearea(vector<int> a) { activearea = a; }
	void nextarea();
	Camera();
	void reset() { currentarea = 0; };
	void setcurrentarea(int a) { currentarea = a; }
	void Setsize(int width, int height);
	void Update(DWORD dt,CGameObject *Simon);
	//center of camera
	void SetFollowtoSimon(bool al) { isfollowSimon = al; }
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);
	void FollowtoSimon(CGameObject *Simon);
	int GetWidth();
	int GetHeight();
	bool checkInCamera(RECT a);
	bool checkInCamera(float t,float l,float r,float b);
	void start_auto();
	bool isautogo() { return autotransiting; }
	D3DXVECTOR3 GetPosition();
	int Getx() { return camx; }
	RECT GetBound();

	~Camera();


};

