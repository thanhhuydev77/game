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

vector<LPGAMEOBJECT> SceneGame::getBoundobjects()
{
	return mmap->getBoundObject();
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
	this->BoundandItemObjects.clear();
	this->BoundObjects.clear();
	this->BrickObjects.clear();
	this->coObjects.clear();
	this->objects.clear();
	this->ItemObjects.clear();
	this->allEnemies.clear();
	this->listeffect.clear();
	CountEnemyGhost = 0;
	CountEnemyPanther = 0;
	CountEnemyBat = 0;
	CountEnemyFishmen = 0;
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
	CGameObject *weapond;
	bool resetsword = false;
	//determine the current weapond
	switch (simon->getcurrentWeapond())
	{
	case Const_Value::Weapond::whip:
		weapond = whip;
		break;
	case Const_Value::Weapond::sword:
		weapond = sword;
		resetsword = true;
		break;
	case Const_Value::Weapond::axe:
		weapond = axe;
		break;
	case Const_Value::Weapond::holywater:
		weapond = holywater;
		break;
	default:
		weapond = whip;
		break;
	}
	for (UINT i = 0; i < BoundandItemObjects.size(); i++)
	{
		if (dynamic_cast<BoundItem *>(BoundandItemObjects.at(i)))
		{
			BoundItem *bounditem = dynamic_cast<BoundItem *>(BoundandItemObjects.at(i));
			if (weapond->CheckOverLap(bounditem))
			{
				
				bounditem->start_disappear();
				if(bounditem->getType() == Const_Value::bound_item_type::Bratizer || bounditem->getType() == Const_Value::bound_item_type::candle)
				listeffect.push_back(new Effect(Const_Value::effect_type::sparks, bounditem->getx(), bounditem->gety(), 0.0f, 0.0f));
				if (bounditem->getType() == Const_Value::bound_item_type::breakableBrick)
				{
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety(),-0.125f,0.0f));
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety(), -0.1125f,0.2f));
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety(), 0.1125f,0.2f));
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety(), 0.125f,0.0f));
				}
				if (bounditem->getType() == Const_Value::bound_item_type::BreakableBlock)
				{
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety()+20, -0.125f, -0.15f));
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety()+20, -0.125f, -0.08f));
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety()+20, -0.125f, 0.15f));
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety()+20, -0.125f, 0.08f));
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety() + 20, 0.125f, -0.15f));
					listeffect.push_back(new Effect(Const_Value::effect_type::broken, bounditem->getx(), bounditem->gety() + 20, 0.125f, 0.08f));
					
				}
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
		//determine enemy's type
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
		if (dynamic_cast<Fishmen *>(allEnemies.at(i)))
		{
			enemy = dynamic_cast<Fishmen *>(allEnemies.at(i));
			type = 4;
		}

		if (enemy != nullptr)
			if (weapond->CheckOverLap(enemy) && enemy->GetState() == ENEMY_STATE_LIVE)
			{
				
				int makeitem = rand() % 6;
				SmallItem *sm = nullptr;
				if (makeitem == 1)
				{
					sm = new SmallItem();
					int randtype = rand() % 12;
					sm->setType(randtype);
					float x, y;
					enemy->GetPosition(x, y);
					sm->SetPosition(x, y);
					sm->SetState(ITEM_STATE_UNACTIVE);
					ItemObjects.push_back(sm);
					objects.push_back(sm);
				}
				switch (type)
				{
				case 1:
					if(makeitem == 1)
					dynamic_cast<Ghost*>(enemy)->addSubItem(sm);
					dynamic_cast<Ghost*>(enemy)->takedamage();
					listeffect.push_back(new Effect(Const_Value::effect_type::sparks, enemy->getx(), enemy->gety()+10, 0.0f, 0.0f));
					break;
				case 2:
					if (makeitem == 1)
						dynamic_cast<Panther*>(enemy)->addSubItem(sm);
					dynamic_cast<Panther*>(enemy)->takedamage();
					listeffect.push_back(new Effect(Const_Value::effect_type::sparks, enemy->getx()+20, enemy->gety(), 0.0f, 0.0f));
					break;
				case 3:
					if (makeitem == 1)
						dynamic_cast<Bat*>(enemy)->addSubItem(sm);
					dynamic_cast<Bat*>(enemy)->takedamage();
					listeffect.push_back(new Effect(Const_Value::effect_type::sparks, enemy->getx(), enemy->gety(), 0.0f, 0.0f));
					break;
				case 4:
					if (makeitem == 1)
						dynamic_cast<Fishmen*>(enemy)->addSubItem(sm);
					dynamic_cast<Fishmen*>(enemy)->takedamage();
					listeffect.push_back(new Effect(Const_Value::effect_type::sparks, enemy->getx(), enemy->gety() + 10, 0.0f, 0.0f));
					break;
				default:
					break;
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
				simon->setnumstep(0);
				simon->setcanclimb(true, true);
				simon->setcanclimb(false, false);
				typestairstart = dynamic_cast<CInvisibleObject*>(allStairpoint.at(i));
				break;
			}
			else if (type == Const_Value::in_obj_type::stairdown) // stair down
			{
				simon->setnumstep(0);
				simon->setcanclimb(true, false);
				simon->setcanclimb(false, true);
				typestairstart = dynamic_cast<CInvisibleObject*>(allStairpoint.at(i));
				break;
			}
			else if (type == Const_Value::in_obj_type::endmap1) // stair down
			{
				resetlist();
				this->LoadContent(2);
				break;
			}
			else if (type == Const_Value::in_obj_type::map2to3_p1)
			{
				float x, y;
				simon->GetPosition(x, y);
				resetlist();
				this->LoadContent(3);
				simon->SetPosition(x, 0.0f);
				//simon->setstateendmap1(false);
				break;
			}
			else if (type == Const_Value::in_obj_type::map2to3_p1)
			{
				float x, y;
				simon->GetPosition(x, y);
				resetlist();
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
					changemap = false;
				}
				//meeting stairup
				else if (type == Const_Value::in_obj_type::stairup)
				{
					
					simon->startAutoClimb(stair->getDirect(), b);
					simon->setTempny(3);
					int optionx = (stair->getDirect() == 1) ? 0 : 20;
					simon->startAutowalk(-stair->getDirect(), l - SIMON_SMALL_BBOX_WIDTH + optionx);
					simon->setTempnx(-stair->getDirect());
					changemap = false;
				}
				else if (type == Const_Value::in_obj_type::map2to3_p1)
				{
					changemap = true;
					resetlist();
					Camera::getInstance()->reset();
					this->LoadContent(3);
					simon->SetPosition(127.0f, OFFSET_Y + 0.0f);
					
					//simon->SetPosition(x, 0.0f);
					//simon->setstateendmap1(false);
					
					break;
				}
				else if (type == Const_Value::in_obj_type::map2to3_p2)
				{
					changemap = true;
					resetlist();
					Camera::getInstance()->reset();
					this->LoadContent(3);
					simon->SetPosition(770.0f, OFFSET_Y + 0.0f);
					
					
					//simon->setstateendmap1(false);
					break;
				}
				else if (type == Const_Value::in_obj_type::map3to2_p1)
				{
					changemap = true;
					resetlist();
					Camera::getInstance()->setcurrentarea(1);
					Camera::getInstance()->SetPosition(3072, 0);
					this->LoadContent(2);
					simon->SetPosition(3160.0f, OFFSET_Y + 290.0f);
					
					
					

					//simon->SetPosition(x, 0.0f);
					//simon->setstateendmap1(false);
					
					break;
				}
				else if (type == Const_Value::in_obj_type::map3to2_p2)
				{
					changemap = true;
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
					
					simon->startAutoClimb(-typestairstart->getDirect(), b -4.0f);
					simon->setTempny(2);
					int optionx = (typestairstart->getDirect() == 1) ? 0 : 30;
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
	{
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
							allEnemies.push_back(new Ghost(Camera::getInstance()->Getx()-GHOST_BBOX_WIDTH, OFFSET_Y + 185 - GHOST_BBOX_HEIGHT, -1));
							CountEnemyGhost++;
							break;
						}
						else
						{

						}
					}
					//down ground
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
								if (randm == 0)  //from left
								{
									allEnemies.push_back(new Ghost(Camera::getInstance()->Getx() + Camera::getInstance()->GetWidth(), groundY - GHOST_BBOX_HEIGHT - 2, -1));
									CountEnemyGhost++;
								}
								else // from right
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
		//DebugOut(L"camx:%d", Camera::getInstance()->Getx());
		//go to panther area from right and left
		if ((Camera::getInstance()->Getx() >= 775 && Camera::getInstance()->Getx() < 800 )|| (Camera::getInstance()->Getx() < 2015 && Camera::getInstance()->Getx() > 2000))
		{
			if (CountEnemyPanther == 0) //whenever die all-->create all
			{

				int directionPanther = abs(REGION_CREATE_PANTHER_LEFT - simon->getx()) < abs(REGION_CREATE_PANTHER_RIGHT - simon->getx()) ? -1 : 1; 
				allEnemies.push_back(new Panther(1398.0f, OFFSET_Y + 159.0f, directionPanther, directionPanther == -1 ? 20.0f : 9.0f, simon));
				allEnemies.push_back(new Panther(1783.0f, OFFSET_Y + 94.f, directionPanther, directionPanther == -1 ? 278.0f : 180.0f, simon));
				allEnemies.push_back(new Panther(1923.0f, OFFSET_Y + 159.0f, directionPanther, directionPanther == -1 ? 68.0f : 66.0f, simon));
				CountEnemyPanther += 3;
			}
		}
		else if ((Camera::getInstance()->Getx() + 500 < 1270 || Camera::getInstance()->Getx() > 2100))
		{
			for (unsigned int i = 0; i < allEnemies.size(); i++)
			{
				if (dynamic_cast<Panther*>(allEnemies[i]))
				{
						allEnemies.erase(allEnemies.begin() + i);
						CountEnemyPanther--;
				}
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
				if (simon->getx() < CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_X)
					allEnemies.push_back(new Bat(Camera::getInstance()->Getx() + Camera::getInstance()->GetWidth() - 10, simon->gety() + 30, -1));
				else if ((simon->getx() > CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_X &&simon->gety() > CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_Y + OFFSET_Y))
					allEnemies.push_back(new Bat(Camera::getInstance()->Getx() - 10, simon->gety() + 30, 1));
				TimeWaitCreateBat = 4000 + (rand() % 3000);
			}
		}
	}
#pragma endregion
#pragma region create fishmen
	if (currentMap == 3)
	{
		if (CountEnemyFishmen < 2)
		{
			DWORD now = GetTickCount();
			if (now - TimeCreateFishmen >= TimeWaitCreateFishmen) // enough time to create
			{
				TimeCreateFishmen = now; // reset time
				float vtx = 0;
				#pragma region depend on simon location to create where fishmen at 
				if (FISHMEN_ZONE_1_LEFT < simon->getx() && simon->getx() <= FISHMEN_ZONE_1_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4);
				}
				if (FISHMEN_ZONE_2_LEFT < simon->getx() && simon->getx() <= FISHMEN_ZONE_2_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_1) : ((rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_4));
				}
				if (FISHMEN_ZONE_3_LEFT < simon->getx() && simon->getx() <= FISHMEN_ZONE_3_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_4) : (FISHMEN_POS_5);
				}
				if (FISHMEN_ZONE_4_LEFT < simon->getx() && simon->getx() <= FISHMEN_ZONE_4_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_3) : (FISHMEN_POS_5);
				}
				if (FISHMEN_ZONE_5_LEFT < simon->getx() && simon->getx() <= FISHMEN_ZONE_5_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_4) : (FISHMEN_POS_6);
				}
				if (FISHMEN_ZONE_6_LEFT < simon->getx() && simon->getx() <= FISHMEN_ZONE_6_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_5) : ((rand() % 2) ? (FISHMEN_POS_7) : (FISHMEN_POS_8));
				}
				if (FISHMEN_ZONE_7_LEFT < simon->getx() && simon->getx() <= FISHMEN_ZONE_7_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_6) : (FISHMEN_POS_8);
				}
				if (FISHMEN_ZONE_8_LEFT < simon->getx() && simon->getx() <= FISHMEN_ZONE_8_RIGHT)
				{
					vtx = (rand() % 2) ? (FISHMEN_POS_6) : (FISHMEN_POS_7);
				}
#pragma endregion
				float vty = FISHMEN_POS_Y;
				int directionFishmen = vtx < simon->getx() ? 1 : -1;
				allEnemies.push_back(new Fishmen(vtx, vty, directionFishmen, simon, &allfireball,&listeffect));
				CountEnemyFishmen++;

				TimeWaitCreateFishmen = 2000 + (rand() % 2000);
			}
		}
	}
#pragma endregion

#pragma region update object
	
	if ((currentGrids != Grid::getInstace()->checkingrid()))
	{
			objects = this->getallobjects();
			BrickObjects = this->getallHidenObjects();
			BoundObjects = this->getBoundobjects();
			ItemObjects = this->getItemobjects();
			//coObjects = this->getallHidenObjects();
			allStaticObject = getallStaticObject();
			BoundandItemObjects = this->getBoundobjects();
			currentGrids = Grid::getInstace()->checkingrid();
	}
	//DebugOut(L"object:%d-brick:%d-bratizer:%d-item:%d-allstatic:%d-ghost:%d-panther:%d",objects.size(),BrickObjects.size(),BratizerObjects.size(),ItemObjects.size(),allStaticObject.size(),CountEnemyGhost,CountEnemyPanther);
	if (simon->isdestroyall())
	{
		for (UINT i = 0; i < allEnemies.size(); i++)
			allEnemies[i]->takedamage();
		simon->setdestroyall(false);
	}
	for (unsigned int i = 0; i < allEnemies.size(); i++)
	{
		if (dynamic_cast<Ghost*>(allEnemies[i]))
		{
			if (!dynamic_cast<Ghost*>(allEnemies[i])->Isdied())
			{
				if(allEnemies[i]->GetState() == ENEMY_STATE_LIVE)
				coObjects.push_back(allEnemies[i]);
				if(!simon->ispause() && !simon->iscollecting())
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
				if (allEnemies[i]->GetState() == ENEMY_STATE_LIVE)
				coObjects.push_back(allEnemies[i]);
				if (!simon->ispause() && !simon->iscollecting())
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
				if (allEnemies[i]->GetState() == ENEMY_STATE_LIVE)
				coObjects.push_back(allEnemies[i]);
				if (!simon->ispause() && !simon->iscollecting())
				allEnemies[i]->Update(dt, &BrickObjects);
			}
			else
			{
				allEnemies.erase(allEnemies.begin() + i);
				//delete(allEnemies[i]);
			}
		} else
		if (dynamic_cast<Fishmen*>(allEnemies[i]))
			{
				if (!dynamic_cast<Fishmen*>(allEnemies[i])->Isdied())
				{
					if (allEnemies[i]->GetState() == ENEMY_STATE_LIVE)
					coObjects.push_back(allEnemies[i]);
					if (!simon->ispause() && !simon->iscollecting())
					allEnemies[i]->Update(dt, &BrickObjects);
				}
				else
				{
					allEnemies.erase(allEnemies.begin() + i);
					CountEnemyFishmen--;
					//delete(allEnemies[i]);
				}
			}
		
	}
	for (UINT i = 0; i < allfireball.size(); i++)
	{
		if (!dynamic_cast<Fireball*>(allfireball[i])->isFinish())
			coObjects.push_back(allfireball[i]);
	}
	for (unsigned int i = 0; i < ItemObjects.size(); i++)
		ItemObjects[i]->Update(dt, &BrickObjects);
	for (unsigned int i = 0; i < BoundObjects.size(); i++)
	{
		BoundObjects[i]->Update(dt);
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
	for (unsigned int i = 0; i < allfireball.size(); i++)
	{
		if (!simon->ispause() && !simon->iscollecting())
		allfireball[i]->Update(dt);
	}
	for (unsigned int i = 0; i < listeffect.size(); i++)
	{
		if(!dynamic_cast<Effect*>(listeffect[i])->Isfinish())
		listeffect[i]->Update(dt);
		else
		{
			listeffect.erase(listeffect.begin() + i);
		}
	}
	simon->Update(dt, &coObjects);
	collisionweapond();
	whip->Update(dt);
	sword->Update(dt);
	axe->Update(dt);
	holywater->Update(dt, &BrickObjects);
	Camera::getInstance()->Update(dt, simon);
	
#pragma endregion
}

void SceneGame::LoadContent(int map)
{
	Camera::getInstance()->Setsize(mapwidth, SCREEN_HEIGHT);
	currentGrids.clear();
	games = CGame::GetInstance();
	CTextures * textures = CTextures::GetInstance();
	textures->loadcontent();
	this->loadmap(map);
	mapwidth = this->getmapwidth();
	typestairstart = new CInvisibleObject();
	objects = this->getallobjects();
	BrickObjects = this->getallHidenObjects();
	BoundObjects = this->getBoundobjects();
	ItemObjects = this->getItemobjects();
	coObjects = this->getallHidenObjects();
	allStaticObject = getallStaticObject();
	BoundandItemObjects = this->getBoundobjects();

	//for (unsigned int i = 0; i < ItemObjects.size(); i++)
	//{
	//	if (ItemObjects[i]->GetState() == ITEM_STATE_ACTIVE)
	//		coObjects.push_back(this->getItemobjects().at(i));
	//	//BratizerandItemObjects.push_back(this->getItemobjects().at(i));
	//}
	//init simon with defaul position
	simon = Simon::getinstance(&listeffect);
	float x, y;
	BrickObjects.at(0)->GetPosition(x, y);
	groundY = y;
	simon->SetPosition(x,y - SIMON_BIG_BBOX_HEIGHT - 1);
	objects.push_back(simon);
	//init sword and whip
	sword = new Sword(simon);
	objects.push_back(sword);
	whip = new Whip(simon);
	objects.push_back(whip);
	axe = new Axe(simon);
	objects.push_back(axe);
	holywater = new Holy_Water(simon);
	objects.push_back(holywater);
	allfireball.push_back(new Fireball(1000, simon->gety(), -1));
	currentGrids = Grid::getInstace()->checkingrid();
	
	
}

void SceneGame::Draw()
{
	if (simon->Gameover())
		return;
	this->RenderBackground();
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	for (unsigned int i = 0; i < allEnemies.size(); i++)
		allEnemies[i]->Render();
	for (unsigned int i = 0; i < allfireball.size(); i++)
		allfireball[i]->Render();
	for (unsigned int i = 0; i < listeffect.size(); i++)
		listeffect[i]->Render();
	simon->Render();
	whip->Render();
	sword->Render();
	axe->Render();
	holywater->Render();


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
		CGameObject *weapond;
		
		if (games->IsKeyDown(DIK_UP) && simon->getcurrentsubWeapondTurn() >= 1)
		{
			switch (simon->getcurrentsubWeapond())
			{
			case Const_Value::Weapond::sword:
				if (sword->GetState() != WEPOND_STATE_ACTIVE)
				{
					simon->StartAttack();
					simon->setcurrentsubWeapondTurnDesc();
					sword->StartAttack();
					simon->setcurrentWeapond(Const_Value::Weapond::sword);
				}
				break;
			case Const_Value::Weapond::axe:
				if (axe->GetState() != WEPOND_STATE_ACTIVE)
				{
					simon->StartAttack();
					simon->setcurrentsubWeapondTurnDesc();
					axe->StartAttack();
					simon->setcurrentWeapond(Const_Value::Weapond::axe);
				}
				break;
			case Const_Value::Weapond::holywater:
				if (holywater->GetState() != WEPOND_STATE_ACTIVE)
				{
					simon->StartAttack();
					simon->setcurrentsubWeapondTurnDesc();
					holywater->StartAttack();
					simon->setcurrentWeapond(Const_Value::Weapond::holywater);
				}
				break;
			default:
				break;
			}
			

		}
		//using whip 
		else
		{
			//animation with whip
			if (!simon->iscollecting() )
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
				simon->setnumstep(0);
				simon->resetlengthstair();
				float l, t, r, b;
				typestairstart->GetBoundingBox(l, t, r, b);
				simon->setTempny(2);

				simon->setstairinfo(typestairstart->Gettype(), typestairstart->getDirect());
				//climb to left
				if (typestairstart->getDirect() == -1)
				{
					simon->startAutowalk(-1, l - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					simon->settempxy(l-20, b);
					
					simon->startAutoClimb(-1, b);
				}
				//climb to right
				else
				{
					simon->settempxy(l-7, b);
					simon->startAutowalk(1, r - SIMON_SMALL_BBOX_WIDTH - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					//simon->setstairinfo(typestairstart->Gettype(), typestairstart->getDirect());
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
				simon->setnumstep(0);
				simon->resetlengthstair();
				float l, t, r, b;
				typestairstart->GetBoundingBox(l, t, r, b);
				simon->setTempny(3);
				simon->setstairinfo(typestairstart->Gettype(), typestairstart->getDirect());
				//climb down to left
				if (typestairstart->getDirect() == -1)
				{
					simon->startAutowalk(-1, l - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					simon->settempxy(l-23,b+16);
					
					simon->startAutoClimb(1, b + 16);
				}
				//climb down to right
				else
				{
					simon->startAutowalk(1, l - (SIMON_BIG_BBOX_WIDTH - SIMON_SMALL_BBOX_WIDTH) / 2);
					simon->settempxy(l,b+16);
					simon->startAutoClimb(-1, b + 16);
				}
			}
		}
		break;

	}
}

void SceneGame::OnKeyUp(int keyCode)
{
	if (simon->isclimbing() && !simon->inAutoMode() &&!changemap)
	{
		float x, y,numstep;
		simon->gettempxy(x, y);
		
		numstep = simon->getnumstep();
		int i = 0;
		if (typestairstart->Gettype() == Const_Value::in_obj_type::stairup)
			i = 1;
		else if (typestairstart->Gettype() == Const_Value::in_obj_type::stairdown)
			i = -1;
		//simon and stair have the same direction
		simon->SetPosition(x + 16 *numstep*typestairstart->getDirect(), y-SIMON_BIG_BBOX_HEIGHT - 16 *numstep*i);
		DebugOut(L"%d",(int)numstep);
		float x1, y1;
		simon->GetPosition(x1, y1);
		DebugOut(L"simonx,y:%f-%f", x1, y1);
	}
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