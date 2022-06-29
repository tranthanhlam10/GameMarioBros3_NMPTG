#pragma once

#include "GameObject.h"

#define MARIO_WORLD_MAP_BBOX_WIDTH 8
#define MARIO_WORLD_MAP_BBOX_HEIGHT 8

#define MARIO_WORLD_MAP_STATE_IDLE 100
#define MARIO_WORLD_MAP_STATE_WALK_RIGHT 200
#define MARIO_WORLD_MAP_STATE_WALK_LEFT 300
#define MARIO_WORLD_MAP_STATE_WALK_TOP 400
#define MARIO_WORLD_MAP_STATE_WALK_BOTTOM 500
#define MARIO_WORLD_MAP_SPEED 0.1f

#define ID_ANI_MARIO_IN_WORLD_MAP 115
#define ID_ANI_MARIO_SMALL_IN_WORLD_MAP 116
#define ID_ANI_MARIO_RACCOON_IN_WORLD_MAP 117
#define ID_ANI_MARIO_FIRE_IN_WORLD_MAP 118	

class WorldPlayer : public CGameObject
{
	int level;
	float ax;
	float ay;
public:
	int allowLeft = 0, allowRight = 1, allowBottom = 0, allowTop = 0;
	WorldPlayer(float x, float y);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - MARIO_WORLD_MAP_BBOX_WIDTH / 2; 
		top = y - MARIO_WORLD_MAP_BBOX_WIDTH / 2;	
		right = left + MARIO_WORLD_MAP_BBOX_HEIGHT; 
		bottom = top + MARIO_WORLD_MAP_BBOX_HEIGHT;
	};
	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithDoor(LPCOLLISIONEVENT e);
	void OnCollisionWithBlockObj(LPCOLLISIONEVENT e);
	void SetState(int state);
	void SetLevel(int l) { level = l; };
	int sceneSwitch = -1;
	
};
