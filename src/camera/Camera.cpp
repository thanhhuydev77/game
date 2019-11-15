#include "Camera.h"

Camera *Camera::_instance = NULL;
Camera * Camera::getInstance()
{
	if (_instance == NULL)
		_instance = new Camera();
	return _instance;
}

Camera::Camera()
{
	isfollowSimon = true;
}

void Camera::Setsize(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPosition = D3DXVECTOR3(0, 0, 0);
}

void Camera::Update(DWORD dt)
{
}


Camera::~Camera()
{

}

void Camera::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
	mPosition = pos;
	CGame::GetInstance()->SetCamPos(pos.x, pos.y);
}

void Camera::FollowtoSimon(CGameObject * Simon)
{
	if (isfollowSimon)
	{
		float cx, cy;
		Simon->GetPosition(cx, cy);
		if (cx >= (SCREEN_WIDTH+300)/ 2 && cx < (mWidth - (SCREEN_WIDTH+300)/2))
			cx -= (SCREEN_WIDTH+300)/2 ;
		else if (cx < (SCREEN_WIDTH+300) / 2)
			cx = 0.0f;
		else if (cx >= mWidth - (SCREEN_WIDTH + 300) / 2)
			cx = mWidth - (SCREEN_WIDTH + 300);

		cy -= SCREEN_HEIGHT / 2;
		camx = cx;
		camy = 0;
		CGame::GetInstance()->SetCamPos(camx, 0.0f /*cy*/);
	}
}

D3DXVECTOR3 Camera::GetPosition()
{
	return mPosition;
}

RECT Camera::GetBound()
{
	RECT bound;

	bound.left	 = mPosition.x+camx;
	bound.right  = bound.left + SCREEN_WIDTH;
	bound.top	 = mPosition.y+camy;
	bound.bottom = bound.top + SCREEN_HEIGHT;

	return bound;
}

int Camera::GetWidth()
{
	return mWidth;
}

int Camera::GetHeight()
{
	return mHeight;
}