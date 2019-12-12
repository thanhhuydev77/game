#pragma once
#include "GameObject.h"
#include "../utility/LoadResourceHelper.h"
#include "../camera/Camera.h"
class Board :
	public CGameObject
{
public:
	Board();
	~Board();

	// Inherited via CGameObject
	virtual void GetBoundingBox(float & left, float & top, float & right, float & bottom) override;
	virtual void Render() override;
};

