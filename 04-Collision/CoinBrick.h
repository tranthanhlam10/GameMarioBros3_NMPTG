#pragma once

#include "GameObject.h"

#define COIN_BRICK_BBOX_WIDTH 16
#define COIN_BRICK_BBOX_HEIGHT 16

#define COIN_ANI_BRICK 0
#define COIN_ANI_BRICK_EMPTY 1
#define ID_ANI_COIN_IDLE 2


#define COIN_BRICK_MAX_HEIGHT 10 
#define COIN_BRICK_SPEED_UP 0.1f
#define COIN_BRICK_SPEED_DOWN 0.1f

#define COIN_BRICK_MUSHROOM 1
#define COIN_BRICK_P_BUTTON 2
#define COIN_BRICK_COIN 3

#define COIN_BRICK_STATE_UP 100
#define COIN_BRICK_STATE_TRANSFORM_COIN 200
#define COIN_BRICK_STATE_NORMAL 300

#define COIN_BRICK_COIN_TIME_OUT 5000

class CoinBrick : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;
	float startY;
	float startX;
	BOOLEAN isTransform = false;

	BOOLEAN isBreak = false;
	ULONGLONG transform_start = -1;

	vector<LPGAMEOBJECT> objects;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking();
	virtual void OnNoCollision(DWORD dt);

public:

	CoinBrick(float x, float y, int model);
	virtual void SetState(int state);
	void SetBreak(int isBreak) { this->isBreak = isBreak; }
	BOOLEAN isUnbox = false;
	BOOLEAN isEmpty = false;
};
