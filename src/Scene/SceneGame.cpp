#include "SceneGame.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

void SceneGame::loadmap(int map)
{

	switch (map)
	{
	case 1:
		mmap = new Map(MAP1, ID_TEX_MAP1);
		break;
	case 2:
		mmap = new Map(MAP2, ID_TEX_MAP2);
		break;
	case 3:
		mmap = new Map(MAP3, ID_TEX_MAP3);
		break;
	default:
		mmap = new Map(MAP1, ID_TEX_MAP1);
		break;
	}
	currentMap = map;


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

vector<LPGAMEOBJECT> SceneGame::getallStaticObject()
{
	return mmap->getallstaticObject();
}

int SceneGame::getmapwidth()
{
	return mmap->GetWidth();
}

void SceneGame::resetlist()
{
	this->BratizerandItemObjects.clear();
	this->BratizerObjects.clear();
	this->BrickObjects.clear();
	this->coObjects.clear();
	this->objects.clear();
	this->ItemObjects.clear();
	this->allEnemies.clear();
	CountEnemyGhost = 0;
	CountEnemyPanther = 0;
}

void SceneGame::RenderBackground()
{
	mmap->Draw();
}

SceneGame::~SceneGame()
{
}

void SceneGame::collisionweapond()
{
	//if (simon->getcurrentWeapond() == Const_Value::Weapond::whip && whip->GetState() == WHIP_STATE_ACTIVE);
	CGameObject *weapond;
	bool resetsword = false;
	switch (simon->getcurrentWeapond())
	{
	case Const_Value::Weapond::whip:
		weapond = whip;
		break;
	case Const_Value::Weapond::sword:
		weapond = sword;
		resetsword = true;
		break;
	default:
		weapond = whip;
		break;
	}
	for (UINT i = 0; i < BratizerandItemObjects.size(); i++)
	{
		if (dynamic_cast<BoundItem *>(BratizerandItemObjects.at(i)))
		{
			BoundItem *bratizer = dynamic_cast<BoundItem *>(BratizerandItemObjects.at(i));
			if (weapond->CheckOverLap(bratizer))
			{
				bratizer->start_disappear();
				if (resetsword)
					sword->reset();
				break;
			}
		}
	}
	for (UINT i = 0; i < allEnemies.size(); i++)
	{
		int type = 0;
		CGameObject *enemy = NULL;
		if (dynamic_cast<Ghost *>(allEnemies.at(i)))
		{
			enemy = dynamic_cast<Ghost *>(allEnemies.at(i));
			type = 1;
		}
		if (dynamic_cast<Panther *>(allEnemies.at(i)))
		{
			enemy = dynamic_cast<Panther *>(allEnemies.at(i));
			type = 2;
		}
		if (dynamic_cast<Bat *>(allEnemies.at(i)))
		{
			enemy = dynamic_cast<Bat *>(allEnemies.at(i));
			type = 3;
		}
		if (enemy != nullptr)
			if (weapond->CheckOverLap(enemy) && enemy->GetState() == ENEMY_STATE_LIVE)
			{
				//ghost
				if (type == 1)
				{
					//25% -->small heart
					int makeitem = rand() % 6;
					//has item
					if (makeitem == 1)
					{
						SmallItem *sm = new SmallItem();
						sm->setType(Const_Value::small_item_type::smallheart);
						float x, y;
						enemy->GetPosition(x, y);
						sm->SetPosition(x, y);
						sm->SetState(ITEM_STATE_UNACTIVE);
						dynamic_cast<Ghost*>(enemy)->addSubItem(sm);
						ItemObjects.push_back(sm);
						objects.push_back(sm);
						
					}
					dynamic_cast<Ghost*>(enemy)->takedamage();
					//CountEnemyGhost-=1;
					
				}
				//panther
				else if (type == 2)
				{
					int makeitem = rand() % 6;
					if (makeitem == 1)
					{
						SmallItem *sm = new SmallItem();
						sm->setType(Const_Value::small_item_type::smallheart);
						float x, y;
						enemy->GetPosition(x, y);
						sm->SetPosition(x, y);
						sm->SetState(ITEM_STATE_UNACTIVE);
						dynamic_cast<Panther*>(enemy)->addSubItem(sm);
						ItemObjects.push_back(sm);
						objects.push_back(sm);
						
					}
					dynamic_cast<Panther*>(enemy)->takedamage();
					//CountEnemyPanther--;
				}
				//bat
				else if (type == 3)
				{
					dynamic_cast<Bat*>(enemy)->takedamage();
					//CountEnemyPanther--;
				}
				if (resetsword)
					sword->reset();
				break;
			}
	}


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
			else if (type == Const_Value::in_obj_type::stairdown) // stair down
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
				this->LoadContent(2);
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
				this->LoadContent(3);
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
				this->LoadContent(3);
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
					simon->startAutoClimb(stair->getDirect(), b);
					simon->setTempny(3);
					int optionx = (stair->getDirect() == 1) ? 0 : 20;
					simon->startAutowalk(-stair->getDirect(), l - SIMON_SMALL_BBOX_WIDTH + optionx);
					simon->setTempnx(-stair->getDirect());
				}
				else if (type == Const_Value::in_obj_type::map2to3_p1)
				{
					resetlist();
					Camera::getInstance()->reset();
					this->LoadContent(3);
					//simon->SetPosition(x, 0.0f);
					//simon->setstateendmap1(false);
					simon->SetPosition(127.0f, OFFSET_Y + 0.0f);
					break;
				}
				else if (type == Const_Value::in_obj_type::map2to3_p2)
				{

					resetlist();
					Camera::getInstance()->reset();
					this->LoadContent(3);
					simon->SetPosition(770.0f, OFFSET_Y + 0.0f);
					//simon->setstateendmap1(false);
					break;
				}
				else if (type == Const_Value::in_obj_type::map3to2_p1)
				{
					resetlist();
					Camera::getInstance()->setcurrentarea(1);
					Camera::getInstance()->SetPosition(3072, 0);
					this->LoadContent(2);

					//simon->SetPosition(x, 0.0f);
					//simon->setstateendmap1(false);
					simon->SetPosition(3160.0f, OFFSET_Y + 290.0f);
					break;
				}
				else if (type == Const_Value::in_obj_type::map3to2_p2)
				{

					resetlist();
					Camera::getInstance()->setcurrentarea(1);
					Camera::getInstance()->SetPosition(3072, 0);
					this->LoadContent(2);

					simon->SetPosition(3806.0f, OFFSET_Y + 290.0f);
					//simon->setstateendmap1(false);
					break;
				}
				break;
			}
			else if (dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->Gettype() == typestairstart->Gettype() && simon->GetDirect() != dynamic_cast<CInvisibleObject*>(allStairpoint.at(i))->getDirect())
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
#pragma region create ghost
	if (currentMap == 2)
		if (GetTickCount() - timecreatGhost > 1000)
		{
			//simon in ghost area 1 and 2

			if (simon->getx() >= GHOST_ACTIVE_AREA_1_LEFT && simon->getx() < GHOST_ACTIVE_AREA_1_RIGHT || simon->getx() > GHOST_ACTIVE_AREA_2_LEFT && simon->getx() < GHOST_ACTIVE_AREA_2_RIGHT)
			{
				if (CountEnemyGhost < 3)
				{
					Ghost *ghost;
					//simon going right
					timecreatGhost = GetTickCount();
					if (simon->getVx() > 0)
					{
						CountEnemyGhost++;
						ghost = new Ghost(Camera::getInstance()->Getx() + Camera::getInstance()->GetWidth(), groundY - GHOST_BBOX_HEIGHT - 2, -1);
					}
					else if (simon->getVx() < 0)
					{
						CountEnemyGhost++;
						ghost = new Ghost(Camera::getInstance()->Getx(), groundY - GHOST_BBOX_HEIGHT - 2, 1);
					}
					else
					{
						int random = rand() % 2;
						if (random == 0) // đi từ bên trái
						{
							CountEnemyGhost++;
							ghost = new Ghost(Camera::getInstance()->Getx() + Camera::getInstance()->GetWidth(), groundY - GHOST_BBOX_HEIGHT - 2, -1);
						}
						else // đi từ bên phải
						{
							CountEnemyGhost++;
							ghost = new Ghost(Camera::getInstance()->Getx(), groundY - GHOST_BBOX_HEIGHT - 2, 1);
						}

					}
					allEnemies.push_back(ghost);
				}
			}
			else if (simon->getx() >= GHOST_ACTIVE_AREA_3_LEFT && simon->getx() < GHOST_ACTIVE_AREA_3_RIGHT)
			{
				if (allEnemies.size() < 3)
				{
					int random = rand() % 2;
					//Ghost *ghost;
					switch (random)
					{
						//up ground
					case 0:
					{
						if (simon->getx() < GHOST_AREA_3_COLUMN1)
						{
							allEnemies.push_back(new Ghost(Camera::getInstance()->Getx() + Camera::getInstance()->GetWidth(), OFFSET_Y + 185 - GHOST_BBOX_HEIGHT, -1));
							CountEnemyGhost++;
							break;
						}
						if (simon->getx() > GHOST_AREA_3_COLUMN2)
						{
							allEnemies.push_back(new Ghost(Camera::getInstance()->Getx(), OFFSET_Y + 185 - GHOST_BBOX_HEIGHT, -1));
							CountEnemyGhost++;
							break;
						}
						else
						{

						}
					}

					case 1:
					{
						if (simon->getVx() > 0)
						{
							allEnemies.push_back(new Ghost(Camera::getInstance()->Getx() + Camera::getInstance()->GetWidth(), OFFSET_Y + 330 - GHOST_BBOX_HEIGHT, -1));
							CountEnemyGhost++;
						}
						else
						{
							if (simon->getVx() < 0)
							{
								allEnemies.push_back(new Ghost(Camera::getInstance()->Getx(), OFFSET_Y + 330 - GHOST_BBOX_HEIGHT, 1));
								CountEnemyGhost++;
							}
							else
							{
								int randm = rand() % 2;
								if (randm == 0) // đi từ bên trái
								{
									allEnemies.push_back(new Ghost(Camera::getInstance()->Getx() + Camera::getInstance()->GetWidth(), groundY - GHOST_BBOX_HEIGHT - 2, -1));
									CountEnemyGhost++;
								}
								else // đi từ bên phải
								{
									allEnemies.push_back(new Ghost(Camera::getInstance()->Getx(), groundY - GHOST_BBOX_HEIGHT - 2, 1));
									CountEnemyGhost++;
								}
							}
						}
					}
					break;
					default:
						break;
					}
					//allEnemies.push_back(ghost);
				}
			}
		}
#pragma endregion
#pragma region create panther
	if (REGION_CREATE_PANTHER_LEFT > simon->getx() || simon->getx() > REGION_CREATE_PANTHER_RIGHT)
	{
		if (CountEnemyPanther == 0) // không còn Panther nào sống thì mới dc tạo lại cả 3
		{

			int directionPanther = abs(REGION_CREATE_PANTHER_LEFT - simon->getx()) < abs(REGION_CREATE_PANTHER_RIGHT - simon->getx()) ? -1 : 1; // hướng mặt của Panther quay về hướng simon
			allEnemies.push_back(new Panther(1398.0f, OFFSET_Y + 0.0f, directionPanther, directionPanther == -1 ? 20.0f : 9.0f, simon));
			allEnemies.push_back(new Panther(1783.0f, OFFSET_Y + 6.0f, directionPanther, directionPanther == -1 ? 278.0f : 180.0f, simon));
			allEnemies.push_back(new Panther(1923.0f, OFFSET_Y + 0.0f, directionPanther, directionPanther == -1 ? 68.0f : 66.0f, simon));
			CountEnemyPanther += 3;
		}
	}
#pragma endregion
#pragma region create bat
	if (simon->getx() > BAT_AREA_LEFT && simon->getx() < BAT_AREA_RIGHT)
	{
		DWORD now = GetTickCount();
		if (GetTickCount() - TimeCreateBat >= TimeWaitCreateBat) 
		{
			TimeCreateBat = now; 
			if (simon->getx() < CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_X || (simon->getx() > CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_X && OFFSET_Y+simon->gety() > CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_Y))
				allEnemies.push_back(new Bat(Camera::getInstance()->Getx()+ Camera::getInstance()->GetWidth() - 10,simon->gety() + 40, -1));
			else
				allEnemies.push_back(new Bat(Camera::getInstance()->Getx() - 10,simon->gety() + 40, 1));
			TimeWaitCreateBat = 4000 + (rand() % 3000);
		}
	}
#pragma endregion

#pragma region update object
	for (unsigned int i = 0; i < allEnemies.size(); i++)
	{
		if (dynamic_cast<Ghost*>(allEnemies[i]))
		{
			if (!dynamic_cast<Ghost*>(allEnemies[i])->Isdied())
			{
				//coObjects.push_back(allEnemies[i]);
				allEnemies[i]->Update(dt, &BrickObjects);
			}
			else
			{
				allEnemies.erase(allEnemies.begin() + i);
				CountEnemyGhost--;
				//delete(allEnemies[i]);
			}
		}else
		if (dynamic_cast<Panther*>(allEnemies[i]))
		{
			if (!dynamic_cast<Panther*>(allEnemies[i])->Isdied())
			{
				//coObjects.push_back(allEnemies[i]);
				allEnemies[i]->Update(dt, &BrickObjects);
			}
			else
			{
				allEnemies.erase(allEnemies.begin() + i);
				CountEnemyPanther--;
				//delete(allEnemies[i]);
			}
		}else
		if (dynamic_cast<Bat*>(allEnemies[i]))
		{
			if (!dynamic_cast<Bat*>(allEnemies[i])->Isdied())
			{
				//coObjects.push_back(allEnemies[i]);
				allEnemies[i]->Update(dt, &BrickObjects);
			}
			else
			{
				allEnemies.erase(allEnemies.begin() + i);
				//delete(allEnemies[i]);
			}
		}
		//BratizerandItemObjects.push_back(allEnemies[i]);
		//DebugOut(L"ghost i x:%d --", allEnemies[i]->getx());
	}
	for (unsigned int i = 0; i < ItemObjects.size(); i++)
		ItemObjects[i]->Update(dt, &BrickObjects);
	//update bratizers
	for (unsigned int i = 0; i < BratizerObjects.size(); i++)
	{
		BratizerObjects[i]->Update(dt);
	}
	for (unsigned int i = 0; i < ItemObjects.size(); i++)
	{
		if (ItemObjects[i]->GetState() == ITEM_STATE_ACTIVE)
			coObjects.push_back(ItemObjects[i]);
	}
	for (unsigned int i = 0; i < allStaticObject.size(); i++)
	{
		allStaticObject[i]->Update(dt);
	}

	simon->Update(dt, &coObjects);
	collisionweapond();
	whip->Update(dt);
	sword->Update(dt);

	Camera::getInstance()->Update(dt, simon);
	//ghost->Update(dt, &BrickObjects);
#pragma endregion

	DebugOut(L"CountEnemyGhost:%d--", CountEnemyGhost);
	DebugOut(L"CountEnemyPanther:%d\n", CountEnemyPanther);
}

void SceneGame::LoadContent(int map)
{
	games = CGame::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->loadcontent();
	this->loadmap(map);
	mapwidth = this->getmapwidth();
	typestairstart = new CInvisibleObject();
	objects = this->getallobjects();
	BrickObjects = this->getallHidenObjects();
	BratizerObjects = this->getBratizerobjects();
	ItemObjects = this->getItemobjects();
	coObjects = this->getallHidenObjects();
	allStaticObject = getallStaticObject();
	BratizerandItemObjects = this->getBratizerobjects();

	for (unsigned int i = 0; i < ItemObjects.size(); i++)
	{
		if (ItemObjects[i]->GetState() == ITEM_STATE_ACTIVE)
			coObjects.push_back(this->getItemobjects().at(i));
		//BratizerandItemObjects.push_back(this->getItemobjects().at(i));
	}
	//init simon with defaul position
	simon = Simon::getinstance();
	float x, y;
	BrickObjects.at(0)->GetPosition(x, y);
	groundY = y;
	simon->SetPosition(x, y - SIMON_BIG_BBOX_HEIGHT - 1);
	/*ghost = new Ghost(x+300,y - GHOST_BBOX_HEIGHT - 2 ,-1);
	objects.push_back(ghost);*/
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
	for (unsigned int i = 0; i < allEnemies.size(); i++)
		allEnemies[i]->Render();
}

void SceneGame::OnKeyDown(int KeyCode)
{
	if (Camera::getInstance()->isautogo())
	{
		return;
	}
	if (simon->inAutoMode())
	{
		return;
	}
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
		if (games->IsKeyDown(DIK_UP) && simon->getswordturn() >= 1 && sword->GetState() == SWORD_STATE_UNACTIVE)
		{
			simon->StartAttack();
			simon->setswordturndesc();
			sword->StartAttack();
			simon->setcurrentWeapond(Const_Value::Weapond::sword);
		}
		//using whip 
		else
		{
			//animation with whip
			if (!simon->iscollecting())
			{
				simon->StartAttack();
				whip->StartAttack();
				simon->setcurrentWeapond(Const_Value::Weapond::whip);
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
					simon->startAutoClimb(1, b);
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
					simon->startAutowalk(-1, l - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					simon->startAutoClimb(1, b + 16);
				}
				//climb down to right
				else
				{
					simon->startAutowalk(1, l - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					simon->startAutoClimb(-1, b + 16);
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
	bool cameraauto = Camera::getInstance()->isautogo();
	if (simon->inAutoMode())
	{
		return;
	}
	//sitting
	if (games->IsKeyDown(DIK_S) && !simon->iscollecting() && !simon->isclimbing() && !cameraauto)
	{
		simon->SetState(SIMON_STATE_SIT);
		//whip->SetState(WHIP_STATE_UNACTIVE);
		//simon->reset();
	}
	//walk to right
	else if (games->IsKeyDown(DIK_RIGHT) && !simon->iscollecting() && !simon->isclimbing() && !simon->isattacking() && !cameraauto)
	{
		if (simon->isOnGround())
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	//walk to left 
	else if (games->IsKeyDown(DIK_LEFT) && !simon->iscollecting() && !simon->isclimbing() && !simon->isattacking() && !cameraauto)
	{
		if (simon->isOnGround())
			simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	//go up
	else if (games->IsKeyDown(DIK_UP) && !simon->iscollecting() && simon->isclimbing() && !cameraauto)
	{
		simon->startclimbup();
	}
	else if (games->IsKeyDown(DIK_DOWN) && !simon->iscollecting() && simon->isclimbing() && !cameraauto)
	{
		simon->startclimbdown();
	}

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