#pragma once
#include <string>
using namespace std;
class Const_Value
{
public:
#pragma region Main

#define WINDOW_CLASS_NAME	L"CASTLEVANIA"
#define MAIN_WINDOW_TITLE	L"CASTLEVANIA"
#define BACKGROUND_COLOR	D3DCOLOR_XRGB(255, 255, 255)
#define SCREEN_WIDTH		200
#define SCREEN_HEIGHT		200
#define MAX_FRAME_RATE		120
#define CAMERA_WIDTH		500
#define CAMERA_HEIGHT		500

#pragma endregion
#pragma region texture

#define ID_TEX_MARIO			0
#define ID_TEX_ENEMY			10
#define ID_TEX_MISC				20
#define ID_TEX_SIMON			1
#define ID_TEX_WHIP				11
#define	ID_TEX_MAP1				9
#define	ID_TEX_BBOX				8
#define ID_TEX_BRATIZER			6
#define ID_TEX_LARGE_HEART		7
#define ID_TEX_WHIP_POWER_UP	5
#define	ID_TEX_SWORD			4
#define ID_TEX_SPARK			3
#define ID_TEX_MAP2				12
#define ID_TEX_MAP3				15
#define ID_TEX_ITEM				13
#define ID_TEX_BITEM			14
#define ID_TEX_STATIC_OBJ		16
#define ID_TEX_GHOST		17
#define ID_TEX_PANTHER		18
#define ID_TEX_FISHMEN		19
#define ID_TEX_GIANTBAT		20
#define ID_TEX_VAMPIREBAT	21
#define ID_TEX_FLAME		22
#define ID_TEX_FIREBALL		23
#define ID_TEX_AXE			24
#define ID_TEX_HOLYWATER	25
#define ID_TEX_EFFECT		26
#define MAP1				"content\\tilemap\\map1.txt"
#define MAP2				"content\\tilemap\\map2.txt"
#define MAP3				"content\\tilemap\\map3.txt"

#define OFFSET_Y		100
#pragma endregion
#pragma region Simon
#define DEADSTAGE					2000
#define SIMON_UNTOUCHABLE_TIME		2000
#define SIMON_TIME_ATTACK_OFF		40
#define SIMON_TIME_COLLECT			1000
#define SIMON_WALKING_SPEED			0.09f 
#define SIMON_JUMP_SPEED_Y			0.28f
#define SIMON_JUMP_SPEED_X			0.08f
#define SIMON_HURT_SPEED_X			0.04f
#define SIMON_HURT_SPEED_Y			0.20f
#define SIMON_JUMP_DEFLECT_SPEED	0.2f
#define SIMON_GRAVITY				0.0005f
#define SIMON_DIE_DEFLECT_SPEED		0.5f
#define SIMON_MAX_LEVEL				3
#define SIMON_STATE_IDLE			0
#define SIMON_STATE_STANDING_ONSTAIR	50
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_JUMP_PLUS		350
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT				500
#define SIMON_STATE_GOUP			600
#define SIMON_STATE_GODOWN			900
#define SIMON_STATE_GOUP_ATTACK		610
#define SIMON_STATE_GODOWN_ATTACK	910
#define SIMON_STATE_ATTACK			700
#define SIMON_STATE_COLLECT			800

#define SIMON_ANI_IDLE				4
#define SIMON_ANI_WALKING			8
#define SIMON_ANI_DIE				12
#define SIMON_ANI_JUMP				5
#define SIMON_ANI_SIT				6
#define SIMON_ANI_GOUP				3
#define SIMON_ANI_GODOWN			2
#define SIMON_ANI_ATTACK			0
#define SIMON_ANI_SIT_ATTACK		7
#define SIMON_ANI_COLLECT			1
#define SIMON_ANI_GOUP_ATTACK		9
#define SIMON_ANI_GODOWN_ATTACK		10
#define SIMON_ANI_TAKEDAMAGE		11


#define SIMON_BIG_BBOX_WIDTH		60
#define SIMON_BIG_BBOX_HEIGHT		66
#define SIMON_SPACING_ONTOP			16
#define	SIMON_SMALL_BBOX_WIDTH		32
#define	SIMON_SMALL_SIT_BBOX_HEIGHT	46
#define	SIMON_SMALL_BBOX_HEIGHT		62
#define SIMON_ATTACK_TIME			400
#define SIMON_JUMP_TIME				1000
#define SIMON_UNTOUCHABLE_TIME		3000
static enum Weapond { whip, sword, axe,holywater };
#pragma endregion
#pragma region enemies
#define ENEMY_STATE_LIVE			1
#define ENEMY_STATE_DIE				2
#pragma region ghost
#define GHOST_ACTIVE_AREA_1_LEFT	80
#define GHOST_ACTIVE_AREA_1_RIGHT	825
#define GHOST_ACTIVE_AREA_2_LEFT	2200
#define GHOST_ACTIVE_AREA_2_RIGHT	2775
#define GHOST_ACTIVE_AREA_3_LEFT	4233
#define GHOST_ACTIVE_AREA_3_RIGHT	4993
#define GHOST_AREA_3_COLUMN1		4412.0f 
#define GHOST_AREA_3_COLUMN2		4590.0f

#define GHOST_SPEED_X		0.09f
#define GHOST_GRAVITY		0.005f
#define GHOST_BBOX_WIDTH	34
#define GHOST_BBOX_HEIGHT	64
#pragma endregion
#pragma region panther
#define REGION_CREATE_PANTHER_LEFT 1038.0f
#define REGION_CREATE_PANTHER_RIGHT 2305.0f

#define PANTHER_VYJUMP 0.3f
#define PANTHER_VXJUMP 0.2f
#define PANTHER_GRAVITY 0.005f
#define PANTHER_GRAVITY_JUMPING 0.001f
#define PANTHER_SPEED_RUNNING 0.18f
#define PANTHER_BBOX_WIDTH	66
#define PANTHER_BBOX_HEIGHT	27
#define PANTHER_RUN_RACE		1000
#pragma endregion
#pragma region bat
#define BAT_AREA_LEFT				3166
#define BAT_AREA_RIGHT				4037
#define CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_X 3590.0f 
#define CREATE_BAT_BOUNDARY_DIVISION_DIRECTION_Y 207.0f 
#define BAT_BBOX_WIDTH				34
#define BAT_BBOX_HEIGHT				34
#define BAT_SPEED_X 0.1f 
#define BAT_SPEED_Y 0.05f
#define DeltaY 20
#pragma endregion
#pragma region fishmen
#define FISHMEN_BBOX_WIDTH				34
#define FISHMEN_BBOX_HEIGHT				66
#define FISHMEN_TIME_LIMIT_WAIT_AFTER_ATTACK 700
#define FISHMEN_GRAVITY 0.0015f
#define FISHMEN_SPEED_X 0.07f
#define FISHMEN_SPEED_Y_UP 0.9f
#define FISHMEN_SPEED_Y_DOWN 0.3f
#define FISHMEN_DX_LIMIT 140 
#define FISHMEN_DX_ATTACK_LIMIT 130 
#define FISHMEN_DY_JUMP 270
#define WATER_LEVEL_HEIGHT	389

#define FISHMEN_ZONE_1_LEFT 0.0f
#define FISHMEN_ZONE_1_RIGHT 128.0f
#define FISHMEN_POS_1 56.0f

#define FISHMEN_ZONE_2_LEFT 128.0f
#define FISHMEN_ZONE_2_RIGHT 261.0f
#define FISHMEN_POS_2 189.0f

#define FISHMEN_ZONE_3_LEFT 261.0f
#define FISHMEN_ZONE_3_RIGHT 393.0f
#define FISHMEN_POS_3 317.0f

#define FISHMEN_ZONE_4_LEFT 393
#define FISHMEN_ZONE_4_RIGHT 506
#define FISHMEN_POS_4 440

#define FISHMEN_ZONE_5_LEFT 506.0f
#define FISHMEN_ZONE_5_RIGHT 642.0f
#define FISHMEN_POS_5 571.0f

#define FISHMEN_ZONE_6_LEFT 642.0f
#define FISHMEN_ZONE_6_RIGHT 764.0f
#define FISHMEN_POS_6 695.0f

#define FISHMEN_ZONE_7_LEFT 764.0f
#define FISHMEN_ZONE_7_RIGHT 891.0f
#define FISHMEN_POS_7 816.0f


#define FISHMEN_ZONE_8_LEFT 891.0f
#define FISHMEN_ZONE_8_RIGHT 1030.0f
#define FISHMEN_POS_8 952.0f

#define FISHMEN_POS_Y 400.0f
#pragma endregion

#pragma region Holy water
#define HOLYWATER_SPEED_X 0.22f
#define HOLYWATER_SPEED_Y 0.18f
#define HOLYWATER_GRAVITY 0.001f
#define HOLYWATER_BBOX_WIDTH	34
#define HOLYWATER_BBOX_HEIGHT	30
#pragma endregion
#pragma endregion
#pragma region backgroundobject

	static enum in_obj_type { Brick, endmap1, stairup, stairdown, map2to3_p1, map2to3_p2, map3to2_p1, map3to2_p2 };
	static enum small_item_type { smallheart, largeheart, whippowerup, holywateritem, sworditem, axeitem, redmoneybag, bluemoneybag, whitemoneybag,cross, stopwatch,invisiblepot, doubleshot,chicken};
	static enum bound_item_type { Bratizer, candle, breakableBrick, BreakableBlock, flame };
	static enum static_obj_type { Door };
#define BRATIZER_STATE_ACTIVE		1
#define BRATIZER_STATE_UNACTIVE		0
#define BRATIZER_BBOX_WIDTH			32
#define BRATIZER_BBOX_HEIGHT		64
#define CANDLE_BBOX_WIDTH			16
#define CANDLE_BBOX_HEIGHT			28
#define BRATIZER_STATE_DISAPPEAR	2
#define BRATIZER_ANI_DISAPPEAR		1
#define ENDPOINT_BBOX_WIDTH			32
#define ENDPOINT_BBOX_HEIGHT		32
#define BRICK_BBOX_WIDTH			32
#define BRICK_BBOX_HEIGHT			32
#define BLOCK_BBOX_WIDTH			32
#define BLOCK_BBOX_HEIGHT			64
#define DOOR_BBOX_WIDTH				24
#define DOOR_BBOX_HEIGHT			96

#pragma endregion
#pragma region whip

#define WEPOND_STATE_ACTIVE			1
#define WEPOND_STATE_UNACTIVE		0
#define WHIP_F1_BBOX_WIDTH			17
#define WHIP_F1_BBOX_HEIGHT			51
#define WHIP_F2_BBOX_WIDTH			33
#define WHIP_F2_BBOX_HEIGHT			39
#define WHIP_F3_BBOX_WIDTH			46
#define WHIP_F3_BBOX_HEIGHT			16
#define WHIP_F3_HLV_BBOX_WIDTH		78
#define WHIP_MAX_LEVEL				3
#pragma endregion
#pragma region sword 

#define SWORD_FLY_SPEED			5.0f
#define SWORD_BBOX_WIDTH		32
#define SWORD_BBOX_HEIGHT		18
#pragma endregion
#pragma region Axe
#define AXE_FLY_SPEED_X		0.20f
#define AXE_FLY_SPEED_Y		0.55f
#define AXE_BBOX_WIDTH		32
#define AXE_BBOX_HEIGHT		28

#define THROWINGAXE_SPEED_X 0.25f
#define THROWINGAXE_SPEED_Y 0.65f
#define THROWINGAXE_GRAVITY 0.0015f
#pragma endregion
#pragma region fireball
#define FIREBALL_SPEED			0.21f
#define FIREBALL_BBOX_WIDTH		15
#define FIREBALL_BBOX_HEIGHT	11
#pragma endregion
#pragma region item
#define ITEM_TIME_APPREARENCE		3000
#define ITEM_STATE_ACTIVE			1
#define ITEM_STATE_UNACTIVE			0
#define ITEM_GRAVITY				0.04f
#define SMALL_HEART_SPEED_X				0.05f
#define SMALL_HEART_AROUNDX			25
#define SMALL_HEART_BBOX_WIDTH		16
#define SMALL_HEART_BBOX_HEIGHT		32
#define LARGE_HEART_BBOX_WIDTH		24
#define LARGE_HEART_BBOX_HEIGHT		20
#define WHIP_POWER_UP_BBOX_WIDTH	32
#define WHIP_POWER_UP_BBOX_HEIGHT	32
#define HOLYWATER_BBOX_WIDTH		32
#define HOLYWATER_BBOX_HEIGHT		32
#define AXE_BBOX_WIDTH				28
#define AXE_BBOX_HEIGHT				28
#define MONEYBAG_BBOX_WIDTH			28
#define MONEYBAG_BBOX_HEIGHT		28
#define CROSS_BBOX_WIDTH			32
#define CROSS_BBOX_HEIGHT			32
#define DOUBLESHOT_BBOX_WIDTH		28
#define DOUBLESHOT_BBOX_HEIGHT		28
#define INVISIBLEPOT_BBOX_WIDTH		29
#define INVISIBLEPOT_BBOX_HEIGHT	36
#define STOPWATCH_BBOX_WIDTH		30
#define STOPWATCH_BBOX_HEIGHT		32
#define CHICKEN_BBOX_WIDTH			32
#define CHICKEN_BBOX_HEIGHT			26
#define DOOR_OPEN_ANI_TIME			3000

#pragma endregion
#pragma region effect
	static enum effect_type {money100,money400,money700,money1000,broken,sparks,water};
#define TIME_ACTIVE 300
#define EFFECT_GRAVITY 0.001
#pragma endregion

};

