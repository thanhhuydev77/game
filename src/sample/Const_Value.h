#pragma once
#include <string>
using namespace std;
class Const_Value
{
public:
#pragma region Main
#define WINDOW_CLASS_NAME L"CASTLEVANIA"
#define MAIN_WINDOW_TITLE L"CASTLEVANIA"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 320

#define MAX_FRAME_RATE 120
#pragma endregion
#pragma region texture

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_SIMON 1
#define ID_TEX_WHIP 11
#define	ID_TEX_MAP1 9
#define	ID_TEX_BBOX 8
#define ID_TEX_BRATIZER 6
#define ID_TEX_LARGE_HEART 7
#define ID_TEX_WHIP_POWER_UP 5
#define	ID_TEX_SWORD 4

#pragma endregion
#pragma region Simon
#define SIMON_TIME_ATTACK_OFF 40
#define SIMON_WALKING_SPEED		0.09f 
#define SIMON_JUMP_SPEED_Y		0.5f
#define SIMON_JUMP_SPEED_X		0.1f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.0025f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f
#define SIMON_MAX_LEVEL 3
#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_JUMP_PLUS		350
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT				500
#define SIMON_STATE_GOUP			600
#define SIMON_STATE_GODOWN			600
#define SIMON_STATE_ATTACK			700


#define SIMON_ANI_IDLE				0
#define SIMON_ANI_WALKING			2
#define SIMON_ANI_DIE				4
#define SIMON_ANI_JUMP				5
#define SIMON_ANI_SIT				7
#define SIMON_ANI_GOUP				3
#define SIMON_ANI_GODOWN			4
#define SIMON_ANI_ATTACK			1
#define SIMON_ANI_SIT_ATTACK		6

#define SIMON_BIG_BBOX_WIDTH		60
#define SIMON_BIG_BBOX_HEIGHT		66
#define	SIMON_SMALL_BBOX_WIDTH		32
#define	SIMON_SMALL_BBOX_HEIGHT		62
#define SIMON_ATTACK_TIME			400
#define SIMON_JUMP_TIME				100
#define SIMON_UNTOUCHABLE_TIME		3000
#pragma endregion
#pragma region backgroundobject
#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32
#define BRATIZER_STATE_ACTIVE 1
#define BRATIZER_STATE_UNACTIVE 0
#define BRATIZER_BBOX_WIDTH  32
#define BRATIZER_BBOX_HEIGHT 64
#pragma endregion
#pragma region whip

#define WHIP_STATE_ACTIVE  1
#define WHIP_STATE_UNACTIVE 0

#define WHIP_F1_BBOX_WIDTH  17
#define WHIP_F1_BBOX_HEIGHT 51
#define WHIP_F2_BBOX_WIDTH  33
#define WHIP_F2_BBOX_HEIGHT 39
#define WHIP_F3_BBOX_WIDTH  46
#define WHIP_F3_BBOX_HEIGHT 16
#define WHIP_F3_HLV_BBOX_WIDTH  78
#define WHIP_MAX_LEVEL 3
#pragma endregion
#pragma region sword 
#define SWORD_FLY_SPEED		5.0f
#define SWORD_STATE_ACTIVE		1
#define SWORD_STATE_UNACTIVE	0
#define SWORD_BBOX_WIDTH		32
#define SWORD_BBOX_HEIGHT		18
#pragma endregion
#pragma region item
#define ITEM_STATE_ACTIVE  1
#define ITEM_STATE_UNACTIVE 0
#define LARGE_HEART_BBOX_WIDTH  24
#define LARGE_HEART_BBOX_HEIGHT 20
#define LARGE_HEART_GRAVITY 0.001f
#define WHIP_POWER_UP_BBOX_WIDTH  32
#define WHIP_POWER_UP_BBOX_HEIGHT 32
#define WHIP_POWER_UP_GRAVITY 0.001f
#pragma endregion
};

