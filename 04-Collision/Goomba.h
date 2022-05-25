#pragma once
#include "GameObject.h"
#include "Collision.h"




#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_RED_WING_STATE_WALKING 300
#define GOOMBA_RED_WING_STATE_JUMP_LOW 400
#define GOOMBA_RED_WING_STATE_JUMP_HIGH 500

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1
#define GOOMBA_ANI_IS_ATTACKED 2
#define GOOMBA_ANI_RED_WALK 3
#define GOOMBA_ANI_RED_WING_WALK 4
#define GOOMBA_ANI_RED_WING_JUMP 5
#define GOOMBA_ANI_RED_WING_IS_ATTACKED 6
#define GOOMBA_ANI_RED_DIE 7

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.03f
#define GOOMBA_IS_ATTACK_SPEED_Y 0.3f
#define GOOMBA_IS_ATTACK_SPEED_X 0.05f
#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_RED_WING_BBOX_HEIGHT 20
#define GOOMBA_RED_WING_BBOX_WIDTH 20
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define LIMIT_HIGH_LOW 0.25f
#define LIMIT_HIGH_JUMP 0.4f
#define LIMIT_TIME_WING_WALKING 1000
#define LIMIT_JUMP_STACK 3

#define JUMP_LOW_SPEED 0.25f
#define JUMP_HIGH_SPEED 0.4f

#define GOOMBA_NOMAL 1
#define GOOMBA_RED_WING 2

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 

	ULONGLONG die_start;
	ULONGLONG wing_walk_start;
	ULONGLONG jump_low_start;
	ULONGLONG jump_high_start;

	BOOLEAN isOnPlatform;
	BOOLEAN isJumping = false;
	BOOLEAN isJumpStart = false;
	BOOLEAN isWalking = false;

	int jumpStack = 0;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int model);
	virtual void SetState(int state);
};