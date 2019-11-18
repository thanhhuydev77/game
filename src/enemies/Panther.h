#pragma once
#include "../sample/GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../map/Invisibleobject.h"
class Panther :
	public CGameObject
{
	bool isSitting;
	bool isRunning;
	bool isJumping;
	bool isStart;
	float AutoGoX_Distance; // khoảng cách cần chạy
	bool isAutoGoX;
	float AutoGoX_Backup_X;
	CGameObject * simon;
	CGameObject *subItem;

	DWORD disappear_start;
	bool disappearing;
public:
	Panther(float X, float Y, int Direction, float autoGoX_Distance, CGameObject * simon);
	bool GetIsStart();
	void start_disappear();
	void addSubItem(CGameObject *sub) { subItem = sub; };
	void takedamage();
	void Jump();
	void Run();
	bool Isdied() { return (Health <= 0); }
	~Panther();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	// Inherited via CGameObject
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

