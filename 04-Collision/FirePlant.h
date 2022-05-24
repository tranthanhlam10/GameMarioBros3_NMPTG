#pragma once

#include "GameObject.h"

#define FP_BBOX_WIDTH 16
#define FP_BIG_BBOX_HEIGHT 33
#define FP_SMALL_BBOX_HEIGHT 25

// ID ANI FPP

// BIG
#define ID_ANI_FP_LEFT_TOP 0
#define ID_ANI_FP_LEFT_BOTTOM 1
#define ID_ANI_FP_LEFT_TOP_SHOOT 2
#define ID_ANI_FP_LEFT_BOTTOM_SHOOT 3
#define ID_ANI_FP_RIGHT_TOP 4
#define ID_ANI_FP_RIGHT_BOTTOM 5
#define ID_ANI_FP_RIGHT_TOP_SHOOT 6
#define ID_ANI_FP_RIGHT_BOTTOM_SHOOT 7

// SMALL
#define ID_ANI_FP_SMALL_LEFT_TOP 8
#define ID_ANI_FP_SMALL_LEFT_BOTTOM 9
#define ID_ANI_FP_SMALL_LEFT_TOP_SHOOT 10
#define ID_ANI_FPP_SMALL_LEFT_BOTTOM_SHOOT 11
#define ID_ANI_FP_SMALL_RIGHT_TOP 12
#define ID_ANI_FP_SMALL_RIGHT_BOTTOM 13
#define ID_ANI_FP_SMALL_RIGHT_TOP_SHOOT 14
#define ID_ANI_FP_SMALL_RIGHT_BOTTOM_SHOOT 15


//MODEL
#define FIRE_PLANT_BIG 1
#define FIRE_PLANT_SMALL 2

//DISTANCE
#define DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO 75
#define DISTANCE_SAFE_ZONE 25

// SPEED
#define FPP_SPEED 0.02f


// TIME
#define FPP_UP_TIME_OUT 4000
#define FPP_DOWN_TIME_OUT 3000
class FirePlant : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;
	float startY;
	int marioRange = 0;

	ULONGLONG down_start = -1;
	ULONGLONG up_start = -1;
	BOOLEAN isMarioSafeZone = false;
	BOOLEAN startShoot = false, startDown = false;
	BOOLEAN isBottom = false, isFar = false;
	vector<LPGAMEOBJECT> TotalFire;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);;
	void PlantShootFire();
public:
	FirePlant(float x, float y, int model);
	void GetMarioRangeCurrent();
};