#include "Camera.h"
Camera *Camera::_instance = NULL;
Camera * Camera::getInstance()
{
	if (_instance == NULL)
		_instance = new Camera();
	return _instance;
}

void Camera::nextarea()
{
	des = camx + 250;
	start_auto();
	currentarea++;
}

Camera::Camera()
{
	isfollowSimon = true;
	currentarea = 0;
}

void Camera::Setsize(int width, int height)
{
	mWidth = width;
	mHeight = height;

	mPosition = D3DXVECTOR3(0, 0, 0);
}

void Camera::Update(DWORD dt, CGameObject *Simon)
{
	if (isfollowSimon)
		FollowtoSimon(Simon);
	else if (autotransiting)
	{
		start_auto();
	}
	//DebugOut(L"autotrasiting :%d --",autotransiting);
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
	camx = pos.x;
	camy = pos.y;
	CGame::GetInstance()->SetCamPos(pos.x, pos.y);
}

void Camera::FollowtoSimon(CGameObject * simon)
{
	if (camx < activearea[currentarea] && !dynamic_cast<Simon *>(simon)->inAutoMode())
	{
		des = activearea[currentarea];
		start_auto();
	}
	else
	{
		float cx, cy;
		simon->GetPosition(cx, cy);
		//GIUA MAP
		if (cx >= (CAMERA_WIDTH) / 2 + activearea[currentarea] && cx < (activearea[currentarea + 1] - (CAMERA_WIDTH) / 2))
			camx = cx - ((CAMERA_WIDTH) / 2);
		//DAU MAP
		else if (cx < (CAMERA_WIDTH) / 2 + activearea[currentarea] && camx >= activearea[currentarea] - 20)
			camx = activearea[currentarea];
		//CUOI MAP
		else if (cx >= activearea[currentarea + 1] - (CAMERA_WIDTH) / 2)
			camx = activearea[currentarea + 1] - (CAMERA_WIDTH)+16;

		cy -= SCREEN_HEIGHT / 2;
		//camx = cx;
		SetPosition(camx, 0.0f);
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

	bound.left	 = camx;
	bound.right  = bound.left + CAMERA_WIDTH;
	bound.top	 = camy;
	bound.bottom = bound.top + CAMERA_HEIGHT;

	return bound;
}

int Camera::GetWidth()
{
	return CAMERA_WIDTH;
}

int Camera::GetHeight()
{
	return mHeight;
}

bool Camera::checkInCamera(RECT a)
{
	if (a.right < camx)
		return false;
	else if (a.left > camx + CAMERA_WIDTH)
		return false;
	return true;
}

bool Camera::checkInCamera(float t, float l, float r, float b)
{
	RECT a;
	a.top = t;
	a.left = l;
	a.right = r;
	a.bottom = b;
	return checkInCamera(a);
}

void Camera::start_auto()
{
	isfollowSimon = false;
	autotransiting = true;
	if (camx < des)
	{
		camx += 2.0f;
		CGame::GetInstance()->SetCamPos(camx, 0);
	}
	else
	{
		autotransiting = false;
		isfollowSimon = true;
	}
}
