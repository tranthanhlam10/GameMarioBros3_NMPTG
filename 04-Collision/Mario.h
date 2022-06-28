#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "TailAttack.h"
#include "debug.h"


#define MARIO_WALKING_SPEED		0.08f 
#define MARIO_ACCEL_WALK_X	0.00015f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_RUNNING_MAX_SPEED 0.3f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f

#define MARIO_GRAVITY			0.0015f

#define MARIO_DECELERATE_SPEED 0.00012f
#define MARIO_DIE_DEFLECT_SPEED	 0.4f

#define MARIO_JUMP_RUN_SPEED_Y	0.5f
#define MARIO_ACCEL_JUMP_Y 0.0005f
#define MARIO_JUMP_SPEED_MIN 0.18f
#define MARIO_JUMP_SPEED_MAX 0.28f

#define MARIO_RACCOON_FLAPPING_SPEED 0.002f
#define MARIO_RACCOON_FALL_SLOW_SPEED 0.025f



#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	1000
#define MARIO_STATE_WALKING_LEFT	2000
#define MARIO_STATE_JUMP			3000
#define MARIO_STATE_RELEASE_JUMP    301
#define MARIO_STATE_DIE				8000
#define MARIO_STATE_SIT						9000
#define MARIO_STATE_RUNNING_RIGHT						4000
#define MARIO_STATE_RUNNING_LEFT						5000
#define MARIO_STATE_SIT_RELEASE						    6000
#define MARIO_STATE_RELEASE_RUN	                        7000
#define MARIO_STATE_SHOOTING							10000
#define MARIO_STATE_KICK							13000
#define MARIO_RACOON_STATE_FLAPPING 11000
#define MARIO_RACOON_STATE_FALL_SLOW 12000
#define MARIO_RACOON_STATE_ATTACK 14000




// mario lon
#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_BIG_WALKING_RIGHT			2
#define MARIO_ANI_BIG_WALKING_LEFT			3
#define MARIO_ANI_BIG_JUMP_RIGHT			4
#define MARIO_ANI_BIG_JUMP_LEFT				5
#define MARIO_ANI_BIG_TURN_RIGHT_BACK_LEFT			6
#define MARIO_ANI_BIG_TURN_LEFT_BACK_RIGHT				7
#define MARIO_ANI_BIG_RUN_RIGHT				8
#define MARIO_ANI_BIG_RUN_LEFT				9
#define MARIO_ANI_BIG_RUN_MAX_RIGHT				10
#define MARIO_ANI_BIG_RUN_MAX_LEFT				11
#define MARIO_ANI_BIG_SIT_RIGHT				12
#define MARIO_ANI_BIG_SIT_LEFT				13
#define MARIO_ANI_BIG_FALL_RIGHT				14
#define MARIO_ANI_BIG_FALL_LEFT				15
#define MARIO_ANI_BIG_JUMP_RUN_RIGHT				16
#define MARIO_ANI_BIG_JUMP_RUN_LEFT				17
#define MARIO_ANI_BIG_HOLD_IDLE_RIGHT				18
#define MARIO_ANI_BIG_HOLD_IDLE_LEFT				19
#define MARIO_ANI_BIG_HOLD_WALK_RIGHT				20
#define MARIO_ANI_BIG_HOLD_WALK_LEFT				21
#define MARIO_ANI_BIG_KICK_RIGHT				22
#define MARIO_ANI_BIG_KICK_LEFT				23
#define MARIO_ANI_BIG_HOLD_JUMP_RIGHT				24
#define MARIO_ANI_BIG_HOLD_JUMP_LEFT				25
#define MARIO_ANI_BIG_TRANSFORM__RIGHT				26
#define MARIO_ANI_BIG_TRANSFORM_LEFT				27

// mario nho
#define MARIO_ANI_SMALL_IDLE_RIGHT		28
#define MARIO_ANI_SMALL_IDLE_LEFT			29
#define MARIO_ANI_SMALL_WALKING_RIGHT		30
#define MARIO_ANI_SMALL_WALKING_LEFT		31
#define MARIO_ANI_SMALL_JUMP_RIGHT			32
#define MARIO_ANI_SMALL_JUMP_LEFT				33
#define MARIO_ANI_SMALL_TURN_RIGHT_BACK_LEFT			34
#define MARIO_ANI_SMALL_TURN_LEFT_BACK_RIGHT				35
#define MARIO_ANI_SMALL_RUN_RIGHT				36
#define MARIO_ANI_SMALL_RUN_LEFT				37
#define MARIO_ANI_SMALL_RUN_MAX_RIGHT				38
#define MARIO_ANI_SMALL_RUN_MAX_LEFT				39
#define MARIO_ANI_SMALL_FALL_RIGHT				40
#define MARIO_ANI_SMALL_FALL_LEFT				41
#define MARIO_ANI_SMALL_JUMP_RUN_RIGHT				42
#define MARIO_ANI_SMALL_JUMP_RUN_LEFT				43
#define MARIO_ANI_SMALL_HOLD_IDLE_RIGHT				44
#define MARIO_ANI_SMALL_HOLD_IDLE_LEFT				45
#define MARIO_ANI_SMALL_HOLD_WALK_RIGHT				46
#define MARIO_ANI_SMALL_HOLD_WALK_LEFT				47
#define MARIO_ANI_SMALL_KICK_RIGHT				48
#define MARIO_ANI_SMALL_KICK_LEFT				49
#define MARIO_ANI_SMALL_HOLD_JUMP_RIGHT				50
#define MARIO_ANI_SMALL_HOLD_JUMP_LEFT				51



// raccoon mario
#define MARIO_ANI_RACOON_IDLE_RIGHT			52
#define MARIO_ANI_RACOON_IDLE_LEFT			53
#define MARIO_ANI_RACOON_WALKING_RIGHT			54
#define MARIO_ANI_RACOON_WALKING_LEFT			55
#define MARIO_ANI_RACOON_JUMP_RIGHT			56
#define MARIO_ANI_RACOON_JUMP_LEFT				57
#define MARIO_ANI_RACOON_TURN_RIGHT_BACK_LEFT			58
#define MARIO_ANI_RACOON_TURN_LEFT_BACK_RIGHT				59
#define MARIO_ANI_RACOON_RUN_RIGHT				60
#define MARIO_ANI_RACOON_RUN_LEFT				61
#define MARIO_ANI_RACOON_RUN_MAX_RIGHT				62
#define MARIO_ANI_RACOON_RUN_MAX_LEFT				63
#define MARIO_ANI_RACOON_SIT_RIGHT				64
#define MARIO_ANI_RACOON_SIT_LEFT				65
#define MARIO_ANI_RACOON_FALL_RIGHT				66
#define MARIO_ANI_RACOON_FALL_LEFT				67
#define MARIO_ANI_RACOON_JUMP_RUN_RIGHT				68
#define MARIO_ANI_RACOON_JUMP_RUN_LEFT				69
#define MARIO_ANI_RACOON_HOLD_IDLE_RIGHT				70
#define MARIO_ANI_RACOON_HOLD_IDLE_LEFT				71
#define MARIO_ANI_RACOON_HOLD_WALK_RIGHT				72
#define MARIO_ANI_RACOON_HOLD_WALK_LEFT				73
#define MARIO_ANI_RACOON_KICK_RIGHT				74
#define MARIO_ANI_RACOON_KICK_LEFT				75
#define MARIO_ANI_RACOON_FLY_RIGHT				76
#define MARIO_ANI_RACOON_FLY_LEFT				77
#define MARIO_ANI_RACOON_FALL_FLY_RIGHT				78
#define MARIO_ANI_RACOON_FALL_FLY_LEFT				79
#define MARIO_ANI_RACOON_FALL_SLOW_RIGHT				80
#define MARIO_ANI_RACOON_FALL_SLOW_LEFT				81
#define MARIO_ANI_RACOON_HOLD_JUMP_RIGHT				82
#define MARIO_ANI_RACOON_HOLD_JUMP_LEFT				83
#define MARIO_ANI_RACOON_TAIL_RIGHT				84
#define MARIO_ANI_RACOON_TAIL_LEFT				85



// mario lua
#define MARIO_ANI_FIRE_IDLE_RIGHT			86
#define MARIO_ANI_FIRE_IDLE_LEFT			87
#define MARIO_ANI_FIRE_WALKING_RIGHT			88
#define MARIO_ANI_FIRE_WALKING_LEFT			89
#define MARIO_ANI_FIRE_JUMP_RIGHT			90
#define MARIO_ANI_FIRE_JUMP_LEFT				91
#define MARIO_ANI_FIRE_TURN_RIGHT_BACK_LEFT			92
#define MARIO_ANI_FIRE_TURN_LEFT_BACK_RIGHT				93
#define MARIO_ANI_FIRE_RUN_RIGHT				94
#define MARIO_ANI_FIRE_RUN_LEFT				95
#define MARIO_ANI_FIRE_RUN_MAX_RIGHT				96
#define MARIO_ANI_FIRE_RUN_MAX_LEFT				97
#define MARIO_ANI_FIRE_SIT_RIGHT				98
#define MARIO_ANI_FIRE_SIT_LEFT				99
#define MARIO_ANI_FIRE_FALL_RIGHT				100
#define MARIO_ANI_FIRE_FALL_LEFT				101
#define MARIO_ANI_FIRE_JUMP_RUN_RIGHT				102
#define MARIO_ANI_FIRE_JUMP_RUN_LEFT				103
#define MARIO_ANI_FIRE_HOLD_IDLE_RIGHT				104
#define MARIO_ANI_FIRE_HOLD_IDLE_LEFT				105
#define MARIO_ANI_FIRE_HOLD_WALK_RIGHT				106
#define MARIO_ANI_FIRE_HOLD_WALK_LEFT				107
#define MARIO_ANI_FIRE_KICK_RIGHT				108
#define MARIO_ANI_FIRE_KICK_LEFT				109
#define MARIO_ANI_FIRE_SHOOT_RIGHT				110
#define MARIO_ANI_FIRE_SHOOT_LEFT				111
#define MARIO_ANI_FIRE_HOLD_JUMP_RIGHT				112
#define MARIO_ANI_FIRE_HOLD_JUMP_LEFT				113

#define MARIO_ANI_DIE				114




#define	MARIO_LEVEL_SMALL		1
#define	MARIO_LEVEL_BIG	2
#define MARIO_LEVEL_RACOON 3
#define MARIO_LEVEL_FIRE 4


#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 20

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 14

#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT))

#define MARIO_UNTOUCHABLE_TIME 5000

#define MARIO_ACCELERATION					0.0003f
#define MARIO_WALKING_MAXSPEED 0.12f

#define ADJUST_MARIO_COLLISION_WITH_COLOR_BLOCK 1

#define MARIO_FIRE_BALL_LIMIT 10
// ADJUST
#define ADJUST_HEIGHT_MARIO_SMALL_TRANSFORM_BIG 10
#define ADJUST_MARIO_SHOOT_FIRE_X 5
#define ADJUST_MARIO_SHOOT_FIRE_Y 5

//time
#define LIMIT_MARIO_RACCOON_FLY_TIME 5000
#define POWER_STACK_TIME 250
#define POWER_STACK_LOST_TIME 250
#define MARIO_FIRE_TIME_SHOOT 500
#define MARIO_TRANSFORM_TIME_OUT 1000
#define MARIO_RACCOON_TRANSFORM_TIME_OUT 500
#define MARIO_KICK_TIMEOUT 300
#define MARIO_RACOON_ATTACK_TIME_OUT 500

#define NUM_OF_EFFECT_MARIO_RACCOON_ATTACK 5 //num of tail attack
#define POSITION_Y_OF_TAIL_MARIO 18 // long for mario head to tail


#define MARIO_POWER_FULL 7


class CMario : public CGameObject // khởi tạo object mario
{
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float start_x;			// initial position of Mario at scene
	float start_y;
	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	

public:
	CMario::CMario(float x = 0.0f , float y = 0.0f) : CGameObject()
	{
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		SetState(MARIO_STATE_IDLE);
		isOnPlatform = false;
		isRunningMax = false;
		maxVx = 0.0f;
		ax = MARIO_ACCELERATION;
		ay = MARIO_GRAVITY; // mario phải chịu tác động của trọng lực hướng xuống
		start_x = x;
		start_y = y;
		this->x = x;
		this->y = y;
		coin = 0;
		tailattack = new TailAttack(x, y);
	}
	
	int coin;

	BOOLEAN isFlying = false;
	BOOLEAN isFlapping = false;
	BOOLEAN isJumping = false;
	BOOLEAN isOnPlatform = false;
	BOOLEAN isRunning = false;
	BOOLEAN isRunningMax = false;
	BOOLEAN isFallSlow = false;
	BOOLEAN isWalking = false;
	BOOLEAN isSitting = false;
	BOOLEAN isMoveOverBlockColor = false;
	BOOLEAN isTransform = false;
	BOOLEAN isPendingShootFireBall = false;
	BOOLEAN isShootingFireBall = false;
	BOOLEAN pendingFallSlow = false;
	BOOLEAN isHoldingTurtle = false;
	BOOLEAN isAdjustHeight = false;
	BOOLEAN isAttack = false;
	BOOLEAN isKickingTurtle = false;
	int runningStack = 0;

	//time
	ULONGLONG flying_start = -1;
	ULONGLONG running_start = -1;
	ULONGLONG running_stop = -1;
	ULONGLONG shoot_start = -1;
	ULONGLONG kick_start = -1;
	ULONGLONG transform_start = -1;
	ULONGLONG attack_start = -1;

	vector<LPGAMEOBJECT> TotalFire;
	
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	void Reset();

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	CGameObject* obj = NULL;
	TailAttack* tailattack;

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e); // va chạm với nấm
	void OnCollisionWithCoin(LPCOLLISIONEVENT e); // va chạm với tiền
	void OnCollisionWithColorBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithFlower(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithMushRoom(LPCOLLISIONEVENT e);
	void OnCollisionWithFireball(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithTwoPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithCoinBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPButton(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() {
		return level;
	}

	int GetCoin() { return coin; }
	void SetCoin(int _coin) { coin = _coin; }

	int LevelDown(){
		return level--;
	}
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	
	void Decelerate();
	void MarioShootFireBall();
	void SetTail();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};