#include "Scene1.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

void Scene1::loadmap(string path, int idtex)
{
	mmap = new Map(path, idtex);
}

vector<LPGAMEOBJECT> Scene1::getallHidenObjects()
{
	return mmap->getallHidenObject();
}

vector<LPGAMEOBJECT> Scene1::getBratizerobjects()
{
	return mmap->getBratizersObject();
}

vector<LPGAMEOBJECT> Scene1::getItemobjects()
{
	return mmap->getItemsObject();
}

vector<LPGAMEOBJECT> Scene1::getallobjects()
{
	return mmap->getallObject();
}

vector<LPGAMEOBJECT> Scene1::getallBrickandpointObjects()
{
	return mmap->getallbrickandpoint();
}

vector<LPGAMEOBJECT> Scene1::getallallStairpoint()
{
	return mmap->getallstairpoint();
}

int Scene1::getmapwidth()
{
	return mmap->GetWidth();
}

void Scene1::RenderBackground()
{
	mmap->Draw();
}

Scene1::~Scene1()
{
}

Scene1::Scene1()
{
	//LoadContent();
}

void Scene1::Update(DWORD dt)
{
	coObjects = this->getallBrickandpointObjects();
#pragma region checkoverlap with stair point --> can climb

	allStairpoint = getallallStairpoint();

	for (int i = 0; i < allStairpoint.size(); i++)
	{
		//walking and meet a stair point
		if (simon->CheckOverLap(allStairpoint.at(i)) && !simon->isclimbing())
		{
			//stair up
			if (dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype() == Const_Value::in_obj_type::stairup)
			{
				simon->setcanclimb(true, true);
				typestairstart = dynamic_cast<CInvisibleObject*>(allStairpoint.at(i));
				break;
			}
			else // stair down
			{
				simon->setcanclimb(true, false);
				typestairstart = dynamic_cast<CInvisibleObject*>(allStairpoint.at(i));
				break;
			}
		}
		//climbing and meet a stair point
		else if (simon->isclimbing() && simon->CheckOverLap(allStairpoint.at(i)))
		{
			if (dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype() != typestairstart->Gettype())
			{
				simon->setclimbing(false);
				DebugOut(L"type stair meeting: %d\n", dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype());
				break;
			}
			else if (dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype() == typestairstart->Gettype())
			{
				simon->setclimbing(false);
				DebugOut(L"type stair meeting: %d\n", dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype());
				break;
			}
		}
		// climbing
		else if (!simon->isclimbing() && !simon->CheckOverLap(allStairpoint.at(i)))
		{
			simon->setcanclimb(false, true);
			simon->setcanclimb(false, false);
			typestairstart = new CInvisibleObject();
			typestairstart->Settype(Const_Value::in_obj_type::Brick);
		}
	}
	DebugOut(L"canclimb up: %d\n", simon->iscanclimbup());
	DebugOut(L"canclimb down: %d\n", simon->iscanclimbdown());
	DebugOut(L"climbing: %d\n", simon->isclimbing());
	DebugOut(L"type stair start: %d\n", typestairstart->Gettype());
	DebugOut(L"type stair start direct: %d\n", typestairstart->getDirect());

#pragma endregion
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
	if (simon->isendmap1())
	{
		this->BratizerandItemObjects.clear();
		this->BratizerObjects.clear();
		this->BrickObjects.clear();
		this->coObjects.clear();
		this->objects.clear();
		this->ItemObjects.clear();
		this->LoadContent(MAP2, ID_TEX_MAP2);
		simon->setstateendmap1(false);
	}

#pragma region Update camera to follow simon

	float cx, cy;
	simon->GetPosition(cx, cy);
	if (cx >= SCREEN_WIDTH / 2 && cx < mapwidth - (SCREEN_WIDTH + 600) / 2)
		cx -= SCREEN_WIDTH / 2 - 10.0f;
	else if (cx < SCREEN_WIDTH / 2)
		cx = 10.0f;
	else if (cx >= mapwidth - (SCREEN_WIDTH + 600) / 2)
		cx = mapwidth - SCREEN_WIDTH - 300;

	cy -= SCREEN_HEIGHT / 2;
	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
#pragma endregion
}

void Scene1::LoadContent(string mapname, int idmap)
{
	games = CGame::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->loadcontent();
	this->loadmap(mapname, idmap);
	mapwidth = this->getmapwidth();
	typestairstart = new CInvisibleObject();
	objects = this->getallobjects();
	BrickObjects = this->getallHidenObjects();
	BratizerObjects = this->getBratizerobjects();
	ItemObjects = this->getItemobjects();
	coObjects = this->getallHidenObjects();
	BratizerandItemObjects = this->getBratizerobjects();

	for (unsigned int i = 0; i < ItemObjects.size(); i++)
	{
		if (ItemObjects[i]->GetState() == ITEM_STATE_ACTIVE)
			coObjects.push_back(this->getItemobjects().at(i));
		BratizerandItemObjects.push_back(this->getItemobjects().at(i));
	}
	//init simon with defaul position
	simon = Simon::getinstance();
	float x, y;
	BrickObjects.at(0)->GetPosition(x, y);
	simon->SetPosition(x, y - SIMON_BIG_BBOX_HEIGHT - 1);
	objects.push_back(simon);
	//init sword and whip
	sword = new Sword(simon);
	objects.push_back(sword);
	whip = new Whip(simon);
	objects.push_back(whip);

}

void Scene1::Draw()
{

	this->RenderBackground();
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void Scene1::OnKeyDown(int KeyCode)
{

	switch (KeyCode)
	{
	case DIK_SPACE:
		if ((games->IsKeyDown(DIK_RIGHT) || games->IsKeyDown(DIK_LEFT) && !simon->isclimbing()))
		{
			simon->StartplexJump();
		}
		else if (!simon->isclimbing())
			simon->StartmonoJump();
		break;
	case DIK_A:

		if (games->IsKeyDown(DIK_UP) && simon->getswordturn() >= 1 && !simon->isclimbing())
		{
			simon->StartAttack();
			simon->setswordturndesc();
			sword->StartAttack();
		}
		else if (!simon->isclimbing())
		{
			//animation with whip
			if (!simon->iscollecting())
			{
				simon->StartAttack();
				whip->StartAttack();
			}
		}
		break;
	}
}

void Scene1::OnKeyUp(int keyCode)
{

}

void Scene1::KeyState(BYTE * states)
{
	if (games->IsKeyDown(DIK_S) && !simon->iscollecting() && !simon->isclimbing())
	{
		simon->SetState(SIMON_STATE_SIT);
		whip->SetState(WHIP_STATE_UNACTIVE);
	}
	else if (games->IsKeyDown(DIK_RIGHT) && !simon->iscollecting() && !simon->isclimbing())
	{
		if (simon->isOnStair())
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (games->IsKeyDown(DIK_LEFT) && !simon->iscollecting() && !simon->isclimbing())
	{
		if (simon->isOnStair())
			simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else if (games->IsKeyDown(DIK_UP) && simon->iscanclimbup())
	{
		if (!simon->isclimbing())
		{
			float l, t, r, b;
			typestairstart->GetBoundingBox(l, t, r, b);
			//climb to left
			if (typestairstart->getDirect() == -1)
				simon->startAutowalk(typestairstart->getDirect(),l+(r-l)/2- (SIMON_BIG_BBOX_WIDTH- SIMON_SMALL_BBOX_WIDTH)/2);
				//simon->startAutoClimb(typestairstart->getDirect(), l - SIMON_SMALL_BBOX_WIDTH, t - SIMON_SMALL_BBOX_HEIGHT + 0.5);  
			else
				simon->startAutowalk(typestairstart->getDirect(),r - (r - l) / 2 -SIMON_SMALL_BBOX_WIDTH- (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
				//simon->startAutoClimb(typestairstart->getDirect(),r,t - SIMON_SMALL_BBOX_HEIGHT + 0.5);  


		}
	}
	else if (games->IsKeyDown(DIK_DOWN) && simon->iscanclimbdown())
	{
		simon->startclimbdown();
	}
	else
	{
		if (!simon->isclimbing())
			simon->SetState(SIMON_STATE_IDLE);
		else
		
			simon->SetState(SIMON_STATE_STANDING_ONSTAIR);
		
	}
}
