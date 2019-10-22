#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "../utility/LoadResourceHelper.h"
#include "../map/Gamemap.h"
#include "Mario.h"
#include "../map/Brick.h"
#include "Goomba.h"
#include "../character/Simon.h"
#include "Const_Value.h"
#include "../weapon/Whip.h"
#include "../weapon/Sword.h"

Sword *sword;
CGame *game;
Simon *simon;
Gamemap *gm;
Whip *whip;
double Scale_rate;
int mapwidth;

vector<LPGAMEOBJECT> objects;  //all object
vector<LPGAMEOBJECT> BratizerObjects; //all bratizer
vector<LPGAMEOBJECT> coObjects;//all object except simon
vector<LPGAMEOBJECT> ItemObjects; //all item object
vector<LPGAMEOBJECT> BrickObjects; // all brick 
vector<LPGAMEOBJECT> BratizerandItemObjects; //all bratizers and items

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (game->IsKeyDown(DIK_RIGHT) || game->IsKeyDown(DIK_LEFT) )
		{
			simon->StartplexJump();
		}
		simon->StartmonoJump();
		break;
	case DIK_A:
		if (game->IsKeyDown(DIK_UP) && !game->IsKeyDown(DIK_DOWN) && !simon->iscollecting())
		{
			if (simon->getswordturn() >= 1 && !simon->isattacking() && !sword->isattacking())
			{  //animation with sword , sword turn - 1
				simon->StartAttack();
				simon->setswordturndesc();
				sword->StartAttack();
			}
		}
		else
		{
			//animation with whip
			if (!simon->isattacking() && !game->IsKeyDown(DIK_DOWN) && !simon->iscollecting())
			{
				simon->StartAttack();
				whip->StartAttack();
			}
		}
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (game->IsKeyDown(DIK_DOWN) && !simon->iscollecting())
	{
		simon->SetState(SIMON_STATE_SIT);
		whip->SetState(WHIP_STATE_UNACTIVE);
	}
	else if (game->IsKeyDown(DIK_RIGHT) && !simon->iscollecting())
	{
		if (simon->isOnState())
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT) && !simon->iscollecting())
	{
		if (simon->isOnState())
			simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else
	{
		if (simon->isOnState())
			simon->SetState(SIMON_STATE_IDLE);
	}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();
	textures->loadcontent();
	gm = new Gamemap();
	gm->loadmap("content\\tilemap\\Courtyard.txt", ID_TEX_MAP1, SCREEN_HEIGHT, SCREEN_WIDTH);
	mapwidth = gm->getmapwidth();

	Scale_rate = gm->getscalerate();
	objects = gm->getallobjects();
	BrickObjects = gm->getBrickobjects();
	BratizerObjects = gm->getBratizerobjects();
	ItemObjects = gm->getItemobjects();
	coObjects = gm->getBrickobjects();
	BratizerandItemObjects = gm->getBratizerobjects();

	for (unsigned int i = 0; i < ItemObjects.size(); i++)
	{
		if (ItemObjects[i]->GetState() == ITEM_STATE_ACTIVE)
			coObjects.push_back(gm->getItemobjects().at(i));
		BratizerandItemObjects.push_back(gm->getItemobjects().at(i));
	}
	//init simon with defaul position
	simon = new Simon(Scale_rate);
	simon->SetPosition(10.0f, 180.0f);
	objects.push_back(simon);
	//init sword and whip
	sword = new Sword(Scale_rate, simon);
	objects.push_back(sword);
	whip = new Whip(Scale_rate, simon);
	objects.push_back(whip);

}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	coObjects = gm->getBrickobjects();
	// item falling and stop when on stair
	for (unsigned int i = 0; i < ItemObjects.size(); i++)
		ItemObjects[i]->Update(dt, &BrickObjects);
	//update bratizers
	for (unsigned int i = 0; i < BratizerObjects.size(); i++)
		BratizerObjects[i]->Update(dt);

	for (unsigned int i = 0; i < ItemObjects.size(); i++)
	{
		if (ItemObjects[i]->GetState() == ITEM_STATE_ACTIVE)
			coObjects.push_back(ItemObjects[i]);
	}
	simon->Update(dt, &coObjects);

	whip->Update(dt, &BratizerandItemObjects);
	sword->Update(dt, &BratizerandItemObjects);

#pragma region Update camera to follow simon

	float cx, cy;
	simon->GetPosition(cx, cy);
	if (cx >= SCREEN_WIDTH / 2 && cx < mapwidth - SCREEN_WIDTH / 2)
		cx -= SCREEN_WIDTH / 2 - 10.0f;
	else if (cx < SCREEN_WIDTH / 2)
		cx = 10.0f;
	else if (cx >= mapwidth - SCREEN_WIDTH / 2)
		cx = mapwidth - SCREEN_WIDTH;

	cy -= SCREEN_HEIGHT / 2;
	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
#pragma endregion
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		gm->Render();
		for (unsigned int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}