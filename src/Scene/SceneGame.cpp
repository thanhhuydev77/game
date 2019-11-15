#include "SceneGame.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

void SceneGame::loadmap(string path, int idtex)
{
	mmap = new Map(path, idtex);
}

vector<LPGAMEOBJECT> SceneGame::getallHidenObjects()
{
	return mmap->getallHidenObject();
}

vector<LPGAMEOBJECT> SceneGame::getBratizerobjects()
{
	return mmap->getBratizersObject();
}

vector<LPGAMEOBJECT> SceneGame::getItemobjects()
{
	return mmap->getItemsObject();
}

vector<LPGAMEOBJECT> SceneGame::getallobjects()
{
	return mmap->getallObject();
}

vector<LPGAMEOBJECT> SceneGame::getallBrickandpointObjects()
{
	return mmap->getallbrickandpoint();
}

vector<LPGAMEOBJECT> SceneGame::getallallStairpoint()
{
	return mmap->getallstairpoint();
}

int SceneGame::getmapwidth()
{
	return mmap->GetWidth();
}

void SceneGame::RenderBackground()
{
	mmap->Draw();
}

SceneGame::~SceneGame()
{
}

SceneGame::SceneGame()
{
	//LoadContent();
}

void SceneGame::Update(DWORD dt)
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
			int type = dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype();
			if (type == Const_Value::in_obj_type::stairup)
			{
				simon->setcanclimb(true, true);
				simon->setcanclimb(false, false);
				typestairstart = dynamic_cast<CInvisibleObject*>(allStairpoint.at(i));
				break;
			}
			else if(type == Const_Value::in_obj_type::stairdown) // stair down
			{
				simon->setcanclimb(true, false);
				simon->setcanclimb(false, true);
				typestairstart = dynamic_cast<CInvisibleObject*>(allStairpoint.at(i));
				break;
			}
			else if (type == Const_Value::in_obj_type::endmap1) // stair down
			{
				this->BratizerandItemObjects.clear();
				this->BratizerObjects.clear();
				this->BrickObjects.clear();
				this->coObjects.clear();
				this->objects.clear();
				this->ItemObjects.clear();
				this->LoadContent(MAP2, ID_TEX_MAP2);
				//simon->setstateendmap1(false);
				break;
			}
			else if (type == Const_Value::in_obj_type::map2to3_p1)
			{
				float x, y;
				simon->GetPosition(x, y);
				this->BratizerandItemObjects.clear();
				this->BratizerObjects.clear();
				this->BrickObjects.clear();
				this->coObjects.clear();
				this->objects.clear();
				this->ItemObjects.clear();
				this->LoadContent(MAP3, ID_TEX_MAP3);
				simon->SetPosition(x, 0.0f);
				//simon->setstateendmap1(false);
				break;
			}
			else if (type == Const_Value::in_obj_type::map2to3_p1)
			{
				float x, y;
				simon->GetPosition(x, y);
				this->BratizerandItemObjects.clear();
				this->BratizerObjects.clear();
				this->BrickObjects.clear();
				this->coObjects.clear();
				this->objects.clear();
				this->ItemObjects.clear();
				this->LoadContent(MAP3, ID_TEX_MAP3);
				simon->SetPosition(x, 0.0f);
				//simon->setstateendmap1(false);
				break;
			}

		}
		//climbing and meet a stair point
		else if (simon->isclimbing() && simon->CheckOverLap(allStairpoint.at(i)))
		{
			//get location of stair
			float l, t, r, b;
			allStairpoint.at(i)->GetBoundingBox(l, t, r, b);
			CInvisibleObject *stair = dynamic_cast<CInvisibleObject*>(allStairpoint.at(i));
			int type = dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype();
			if (dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype() != typestairstart->Gettype())
			{
				//meetting stairdown
				if (type == Const_Value::in_obj_type::stairdown)
				{
					simon->startAutoClimb(-stair->getDirect(), b);
					simon->setTempny(2);
					int optionx = (stair->getDirect() == 1) ? 0 : 20;
					simon->startAutowalk(-stair->getDirect(), l - SIMON_SMALL_BBOX_WIDTH + optionx);
					simon->setTempnx(-stair->getDirect());
				}
				//meeting stairup
				else if (type == Const_Value::in_obj_type::stairup)
				{
					simon->startAutoClimb(stair->getDirect(),b);
					simon->setTempny(3);
					int optionx = (stair->getDirect() == 1) ? 0 : 20;
					simon->startAutowalk(-stair->getDirect(), l - SIMON_SMALL_BBOX_WIDTH + optionx);
					simon->setTempnx(-stair->getDirect());
				}
				else if (type == Const_Value::in_obj_type::map2to3_p1)
				{
					float x, y;
					simon->GetPosition(x, y);
					this->BratizerandItemObjects.clear();
					this->BratizerObjects.clear();
					this->BrickObjects.clear();
					this->coObjects.clear();
					this->objects.clear();
					this->ItemObjects.clear();
					this->LoadContent(MAP3, ID_TEX_MAP3);
					//simon->SetPosition(x, 0.0f);
					//simon->setstateendmap1(false);
					simon->SetPosition(127.0f,OFFSET_Y+0.0f);
					break;
				}
				else if (type == Const_Value::in_obj_type::map2to3_p2)
				{
					
					this->BratizerandItemObjects.clear();
					this->BratizerObjects.clear();
					this->BrickObjects.clear();
					this->coObjects.clear();
					this->objects.clear();
					this->ItemObjects.clear();
					this->LoadContent(MAP3, ID_TEX_MAP3);
					simon->SetPosition(770.0f, OFFSET_Y + 0.0f);
					//simon->setstateendmap1(false);
					break;
				}
				else if (type == Const_Value::in_obj_type::map3to2_p1)
				{
					float x, y;
					simon->GetPosition(x, y);
					this->BratizerandItemObjects.clear();
					this->BratizerObjects.clear();
					this->BrickObjects.clear();
					this->coObjects.clear();
					this->objects.clear();
					this->ItemObjects.clear();
					this->LoadContent(MAP2, ID_TEX_MAP2);
					//simon->SetPosition(x, 0.0f);
					//simon->setstateendmap1(false);
					simon->SetPosition(3176.0f, OFFSET_Y + 290.0f);
					break;
				}
				else if (type == Const_Value::in_obj_type::map3to2_p2)
				{

					this->BratizerandItemObjects.clear();
					this->BratizerObjects.clear();
					this->BrickObjects.clear();
					this->coObjects.clear();
					this->objects.clear();
					this->ItemObjects.clear();
					this->LoadContent(MAP2, ID_TEX_MAP2);
					simon->SetPosition(3822.0f, OFFSET_Y + 290.0f);
					//simon->setstateendmap1(false);
					break;
				}
				break;
			}
			else if (dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype() == typestairstart->Gettype() &&simon->GetDirect() != dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->getDirect())
			{
				//meetting stairup
				if (typestairstart->Gettype() == Const_Value::in_obj_type::stairup)
				{

					simon->startAutoClimb(typestairstart->getDirect(), b);
					simon->setTempny(3);
					int optionx = (typestairstart->getDirect() == 1) ? 0 : 20;
					simon->startAutowalk(-typestairstart->getDirect(), l - SIMON_SMALL_BBOX_WIDTH + optionx);
					simon->setTempnx(-typestairstart->getDirect());
					
				}
				//meeting stairdown
				else if (typestairstart->Gettype() == Const_Value::in_obj_type::stairdown)
				{
					simon->startAutoClimb(-typestairstart->getDirect(), b + 4.0f);
					simon->setTempny(2);
					int optionx = (typestairstart->getDirect() == 1) ? 0 : 20;
					simon->startAutowalk(-typestairstart->getDirect(), l - SIMON_SMALL_BBOX_WIDTH + optionx);
					simon->setTempnx(typestairstart->getDirect());
				}
				break;
			}
		}
		// climbing
		else if (simon->isclimbing())
		{
			simon->setcanclimb(true, false);
			simon->setcanclimb(true, true);
		}
		//walking 
		else if (!simon->isclimbing() && !simon->CheckOverLap(allStairpoint.at(i)))
		{
			simon->setcanclimb(false, true);
			simon->setcanclimb(false, false);
			typestairstart = new CInvisibleObject();
			typestairstart->Settype(Const_Value::in_obj_type::Brick);
		}
	}

	/*DebugOut(L"canclimb up: %d --", simon->iscanclimbup());
	DebugOut(L"canclimb down: %d --", simon->iscanclimbdown());
	DebugOut(L"climbing: %d --", simon->isclimbing());
	DebugOut(L"type stair start: %d --", typestairstart->Gettype());
	DebugOut(L"type stair start direct: %d --", typestairstart->getDirect());
	DebugOut(L"simon direct: %d --", simon->GetDirect());*/
	/*DebugOut(L"simon istattacking: %d --", simon->isattacking());*/

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
	

#pragma region Update camera to follow simon

	//float cx, cy;
	//simon->GetPosition(cx, cy);

	//if (cx >= SCREEN_WIDTH / 2 && cx < mapwidth - (SCREEN_WIDTH + 600) / 2)
	//	cx -= SCREEN_WIDTH / 2 - 10.0f;
	//else if (cx < SCREEN_WIDTH / 2)
	//	cx = 10.0f;
	//else if (cx >= mapwidth - (SCREEN_WIDTH + 600) / 2)
	//	cx = mapwidth - SCREEN_WIDTH - 300;

	//cy -= SCREEN_HEIGHT / 2;
	//CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	Camera::getInstance()->FollowtoSimon(simon);
	//float x1, y1, x2, y2;
	RECT a = Camera::getInstance()->GetBound();
	DebugOut(L"left:%d --top:%d --right:%d --bottom:%d \n",a.left,a.top,a.right,a.bottom);
#pragma endregion
}

void SceneGame::LoadContent(string mapname, int idmap)
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
	Camera::getInstance()->Setsize(mapwidth, SCREEN_HEIGHT);
}

void SceneGame::Draw()
{

	this->RenderBackground();
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

void SceneGame::OnKeyDown(int KeyCode)
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
		//using knife
		if (games->IsKeyDown(DIK_UP) && simon->getswordturn() >= 1)
		{
			simon->StartAttack();
			simon->setswordturndesc();
			sword->StartAttack();
		}
		//using whip 
		else 
		{
			//animation with whip
			if (!simon->iscollecting())
			{
				simon->StartAttack();
				whip->StartAttack();
			}
		}
		break;

	case DIK_UP:
		if (simon->iscanclimbup() && !simon->isattacking())
		{
			if (!simon->isclimbing())
			{
				float l, t, r, b;
				typestairstart->GetBoundingBox(l, t, r, b);
				simon->setTempny(2);
				//climb to left
				if (typestairstart->getDirect() == -1)
				{
					simon->startAutowalk(-1, l - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					simon->startAutoClimb(-1, b);
				}
				//climb to right
				else
				{
					simon->startAutowalk(1, r - SIMON_SMALL_BBOX_WIDTH - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					simon->startAutoClimb(1,b);
				}

			}
		}
		break;
	case DIK_DOWN:
		if (simon->iscanclimbdown())
		{

			if (!simon->isclimbing())
			{
				float l, t, r, b;
				typestairstart->GetBoundingBox(l, t, r, b);
				simon->setTempny(3);
				//climb down to left
				if (typestairstart->getDirect() == -1)
				{
					simon->startAutowalk(-1,l - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					simon->startAutoClimb(1,b+16);
				}
				//climb down to right
				else
				{
					simon->startAutowalk(1,l - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					simon->startAutoClimb(-1,b+16);
				}
			}
		}
		break;
		
	}
}

void SceneGame::OnKeyUp(int keyCode)
{

}

void SceneGame::KeyState(BYTE * states)
{
	if (simon->inAutoMode())
	{
		return;
	}
	//sitting
	if (games->IsKeyDown(DIK_S) && !simon->iscollecting() && !simon->isclimbing())
	{
			simon->SetState(SIMON_STATE_SIT);
			//whip->SetState(WHIP_STATE_UNACTIVE);
			//simon->reset();
	}
	//walk to right
	else if (games->IsKeyDown(DIK_RIGHT) && !simon->iscollecting() && !simon->isclimbing() && !simon->isattacking())
	{
		if (simon->isOnGround())
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	//walk to left 
	else if (games->IsKeyDown(DIK_LEFT) && !simon->iscollecting() && !simon->isclimbing() && !simon->isattacking())
	{
		if (simon->isOnGround())
			simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	//go up
	else if (games->IsKeyDown(DIK_UP) && !simon->iscollecting() && simon->isclimbing())
	{
		simon->startclimbup();
	}
	else if (games->IsKeyDown(DIK_DOWN) && !simon->iscollecting() && simon->isclimbing())
	{
		simon->startclimbdown();
	}
	//else if (games->IsKeyDown(DIK_UP) && simon->iscanclimbup())
	//{
	//	{
	//		if (!simon->isclimbing() )
	//		{
	//			float l, t, r, b;
	//			typestairstart->GetBoundingBox(l, t, r, b);
	//			//climb to left
	//			if (typestairstart->getDirect() == -1)
	//			{
	//				simon->startAutowalk(typestairstart->getDirect(), l - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
	//				simon->startAutoClimb(typestairstart->getDirect(), l, t);
	//			}
	//			else
	//			{
	//				simon->startAutowalk(typestairstart->getDirect(), r - SIMON_SMALL_BBOX_WIDTH - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
	//				simon->startAutoClimb(typestairstart->getDirect(), r, t);
	//			}

	//		}
	//		else if(!simon->inAutoMode())
	//		{
	//			simon->startclimbup();
	//		}
	//	}
	//}
	////go down
	//else if (games->IsKeyDown(DIK_DOWN) && simon->iscanclimbdown())
	//{
	//	simon->startclimbdown();
	//}
	//something else
	else
	{
		//idle
		if (!simon->isclimbing())
			simon->SetState(SIMON_STATE_IDLE);
		else
			//standing on stair
			simon->SetState(SIMON_STATE_STANDING_ONSTAIR);

	}

}