#pragma once
#include "Game.h"
#include "Mario.h"
#include "Map.h"

#define DISTANCE_TO_MARIO_X					120
#define DISTANCE_TO_MARIO_Y					5
#define DISTANCE_MARIO_FLY_THROUGH_SKY_Y	265
#define CAMERA_COORDINATE_Y					220
#define CAMERA_ROOT_Y						0
#define WORLD_MAP_CAM_POS_X	20
#define WORLD_MAP_CAM_POS_Y	20

#define MAP1_1							1
#define MAP1_1_1							2
#define  WORLDMAP						3
#define CAMERA_ON_CLOUD			190
#define CAMERA_ON_CLOUD_FIX		170
#define CAMERA_ON_CLOUD_SPEED	20
#define CAMERA_MAP1_1_1_Y		200
#define CAMERA_MAX				2500
#define CAMERA_END_GAME_DIFF	7
#define CAMERA_REFRESH_RATE		10
using namespace std;

class Camera {
public:
	DWORD sum_dt;
	bool isTurnOn = false; // kiểm tra xem camera có bật hay không
	float cxMin, __cx, px, py;
	int sw, sh; float mw, mh;
	int cxMax = CAMERA_MAX;
	int __cy = CAMERA_COORDINATE_Y;
	CMario* mario;
	CGame* game = CGame::GetInstance();
	Map* map;
	Camera(CMario* mario, CGame* game, Map* map);
	virtual void Update(DWORD dt);
};


