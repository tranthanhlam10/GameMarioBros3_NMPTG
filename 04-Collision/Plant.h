#pragma once
#include "GameObject.h"

#define PIRANHA_PLANT_BBOX_WIDTH 16
#define PIRANHA_PLANT_BBOX_HEIGHT 25

#define PIRANHA_PLANT_DOWN_TIME_OUT 3000
#define PIRANHA_PLANT_UP_TIME_OUT 3000

#define ID_ANI_PIRANHA_PLANT 0
#define PIRANHA_STATE_UP 100
#define PIRANHA_STATE_DOWN 200
#define PIRANHA_SPEED 0.02f;
#define DISTANCE_MARIO_SAFE_ZONE 30

class Plant : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;
	float startY;
	ULONGLONG down_start = -1;
	ULONGLONG up_start = -1;
	BOOLEAN isMarioSafeZone = false;


	BOOLEAN startUp = false, startDown = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

public:
	Plant(float x, float y );
	virtual void SetState(int state);
};
