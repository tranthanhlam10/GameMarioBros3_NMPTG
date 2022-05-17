#pragma once
#include "GameObject.h"
#define LOAD_MUSHROOM_FROM_TXT 5
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16
#define MUSHROOM_GRAVITY 0.003f;

#define ID_ANI_RED_MUSHROOM	0
#define ID_ANI_GREEN_MUSHROOM 1

#define MUSHROOM_RUN_SPEED 0.08f;
#define MUSHROOM_SPEED_UP 0.03f;

#define MUSHROOM_STATE_UP 100
#define MUSHROOM_STATE_RUN 200

#define RED_MUSHROOM 1
#define GREEN_MUSHROOM 2

class MushRoom : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;

	BOOLEAN isWalking = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	MushRoom(float x, float y, int model);
	virtual void SetState(int state);
	int GetModel() { return model; }
};

