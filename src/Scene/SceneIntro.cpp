#include "SceneIntro.h"

SceneIntro::SceneIntro()
{
}

SceneIntro::~SceneIntro()
{
}

void SceneIntro::Update(DWORD dt)
{
	simon->Update(dt,&object);
	if (!simon->inAutoMode())
	{
		simon->SetState(SIMON_STATE_TURN_BACK);
		if (timewait == 0)
			timewait = GetTickCount();
		else if (GetTickCount() - timewait > 2500)
		{
			simon->resetToDefault();
			mCamera->reset();

			SceneManager::getInstance()->ReplaceScene(new SceneGame());
			SceneManager::getInstance()->GetCurrentScene()->LoadContent(1);
		}
	}
}

void SceneIntro::LoadContent(int map)
{
	
	Sound::getInstance()->play("Game_Start_Prologue", false,1);
	object.clear();
	vector<int> a = { 0,512 };
	mCamera = Camera::getInstance();
	mCamera->setactivearea(a);
	mCamera->setcurrentarea(0);
	games = CGame::GetInstance();
	CTextures::GetInstance()->loadcontent();
	simon = new Simon();
	inbrick = new CInvisibleObject();
	inbrick->Settype(Const_Value::in_obj_type::Brick);
	inbrick->SetPosition(0, 315);
	inbrick->setsize(600, 32);
	simon->SetPosition(512-SIMON_BIG_BBOX_WIDTH,318-SIMON_BIG_BBOX_HEIGHT);
	simon->startAutowalk(1, 233,0.9);
	object.push_back(inbrick);
}

void SceneIntro::Draw()
{
	CGame::GetInstance()->Draw(0, 0, CTextures::GetInstance()->Get(ID_TEX_INTRO), 0, 0,500,600,255);
	inbrick->Render();
	simon->Render();
}

void SceneIntro::OnKeyDown(int keyCode)
{
}

void SceneIntro::OnKeyUp(int keyCode)
{
}

void SceneIntro::KeyState(BYTE * states)
{
}
