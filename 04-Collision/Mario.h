#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"


#define MARIO_WALKING_SPEED		0.00015f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	1000
#define MARIO_STATE_WALKING_LEFT	2000
#define MARIO_STATE_JUMP			3000
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_DIE				8000
#define MARIO_STATE_SIT						9000





// mario lon
#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_BIG_WALKING_RIGHT			2
#define MARIO_ANI_BIG_WALKING_LEFT			3
#define MARIO_ANI_BIG_JUMP_RIGHT			4
#define MARIO_ANI_BIG_JUMP_LEFT				5
#define MARIO_ANI_BIG_TURN_RIGHT_BACK_LEFT			6
#define MARIO_ANI_BIG_TURN_LEFT_BACK_RIGHT				7

// mario nho
#define MARIO_ANI_SMALL_IDLE_RIGHT		8
#define MARIO_ANI_SMALL_IDLE_LEFT			9
#define MARIO_ANI_SMALL_WALKING_RIGHT		10
#define MARIO_ANI_SMALL_WALKING_LEFT		11
#define MARIO_ANI_SMALL_JUMP_RIGHT			12
#define MARIO_ANI_SMALL_JUMP_LEFT				13

// raccoon mario
#define MARIO_ANI_RACOON_IDLE_RIGHT			14
#define MARIO_ANI_RACOON_IDLE_LEFT			15
#define MARIO_ANI_RACOON_WALK_RIGHT			16
#define MARIO_ANI_RACOON_WALK_LEFT			17
#define MARIO_ANI_RACOON_JUMP_RIGHT			18
#define MARIO_ANI_RACOON_JUMP_LEFT				19



// mario lua
#define MARIO_ANI_FIRE_IDLE_RIGHT			20
#define MARIO_ANI_FIRE_IDLE_LEFT			21
#define MARIO_ANI_FIRE_WALK_RIGHT			22
#define MARIO_ANI_FIRE_WALK_LEFT			23
#define MARIO_ANI_FIRE_JUMP_RIGHT			24
#define MARIO_ANI_FIRE_JUMP_LEFT				25

#define MARIO_ANI_DIE				26




#define	MARIO_LEVEL_BIG		1
#define	MARIO_LEVEL_SMALL	2
#define MARIO_LEVEL_RACOON 3
#define MARIO_LEVEL_FIRE 4


#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 24

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000

#define MARIO_ACCELERATION					0.0003f
#define MARIO_WALKING_MAXSPEED 0.12f





class CMario : public CGameObject // khởi tạo object mario
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float start_x;			// initial position of Mario at scene
	float start_y;
	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 


	// mario bay
	bool isFlying = false;
	BOOLEAN isJumping = false;
	BOOLEAN isOnFlatform = false;
	


	void OnCollisionWithGoomba(LPCOLLISIONEVENT e); // va chạm với nấm
	void OnCollisionWithCoin(LPCOLLISIONEVENT e); // va chạm với tiền


public:
	CMario::CMario(float x = 0.0f , float y = 0.0f) : CGameObject()
	{
		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		SetState(MARIO_STATE_IDLE);
		isSitting = false;
		isOnPlatform = false;
		maxVx = 0.0f;
		ax = MARIO_ACCELERATION;
		ay = MARIO_GRAVITY; // mario phải chịu tác động của trọng lực hướng xuống
		start_x = x;
		start_y = y;
		this->x = x;
		this->y = y;
		//eType = Type::MARIO;
	}

	
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void Reset();
	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	//int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }


	void WalkRight();
	void WalkLeft();

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};