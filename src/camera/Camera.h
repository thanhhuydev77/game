#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../sample/GameObject.h"
#include "../sample/Game.h"
class Camera
{
	static Camera * _instance;
	int             mWidth,mHeight;
	D3DXVECTOR3     mPosition;
	bool isfollowSimon;
	float camx, camy;

public:
	static Camera *getInstance();
	Camera();
	void Setsize(int width, int height);
	void Update(DWORD dt);
	//center of camera
	void SetFollowtoSimon(bool al) { isfollowSimon = al; }
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR3 pos);
	void FollowtoSimon(CGameObject *Simon);
	int GetWidth();
	int GetHeight();

	D3DXVECTOR3 GetPosition();
	RECT GetBound();

	~Camera();


};

