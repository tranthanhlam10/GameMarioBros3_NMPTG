#pragma once

#include "GameObject.h"

#define ID_ANI_HAMMER_WORLD_MAP_WALK_RIGHT 0
#define ID_ANI_HAMMER_WORLD_MAP_WALK_LEFT 1

#define HAMMER_WORLD_MAP_WALK_SPEED 0.01f
#define HAMMER_WORLD_MAP_LIMIT_WALK 16

#define HAMMER_WORLD_MAP_STATE_WALK 100
#define HAMMER_WORLD_MAP_STATE_WALK_LEFT 200
class Hammer : public CGameObject
{
	float limitRight;
	float ax;
	float ay;
	float startX;
	int nx;
public:
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
	virtual void SetState(int state);
	Hammer(float x, float y);
};

