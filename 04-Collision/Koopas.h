#pragma once
#include "GameObject.h"
#include "Collision.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.02f
#define KOOPAS_IS_KICKED_SPEED 0.18f
#define KOOPAS_SPEED_Y_IS_FIRE_ATTACKED 0.4f
#define KOOPAS_SPEED_Y_IS_TAIL_ATTACKED 0.4f
#define KOOPAS_SPEED_X_IS_TAIL_ATTACKED 0.05f
#define KOOPAS_RED_WING_SPEED_X 0.03f

#define KOOPAS_WING_GRAVITY 0.0002f
#define KOOPAS_WING_JUMP_SPEED 0.15f
#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DEFEND 16
#define ADJUST_POSITION_KOOPAS_HELD 13
#define KOOPAS_COMBACK_HEIGHT_ADJUST 0.15f
#define KOOPAS_BOUNCE_SPEED 0.3f


#define KOOPAS_DEFEND_TIMEOUT 8000 
#define KOOPAS_COMBACK_START 6000 


#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DEFEND 200
#define KOOPAS_STATE_IS_KICKED 300
#define KOOPAS_STATE_UPSIDE 400
#define KOOPAS_STATE_JUMP 500


#define KOOPAS_ANI_WALKING_RIGHT 0
#define KOOPAS_ANI_WALKING_LEFT 1
#define KOOPAS_ANI_DEFEND 2
#define KOOPAS_ANI_IS_KICKED 3
#define KOOPAS_ANI_IS_UPSIDE 4
#define KOOPAS_ANI_COMEBACK 5
#define KOOPAS_ANI_UPSIDE_ISKICKED 6
#define KOOPAS_ANI_UPSIDE_COMEBACK 7 
#define KOOPAS_ANI_GREEN_WING_RIGHT 8
#define KOOPAS_ANI_GREEN_WING_LEFT 9

// KOOPAS RED
#define KOOPAS_ANI_RED_WALKING_RIGHT 10
#define KOOPAS_ANI_RED_WALKING_LEFT 11
#define KOOPAS_ANI_RED_DEFEND 12
#define KOOPAS_ANI_RED_IS_KICKED 13
#define KOOPAS_ANI_RED_IS_UPSIDE 14
#define KOOPAS_ANI_RED_COMEBACK 15
#define KOOPAS_ANI_RED_UPSIDE_ISKICKED 16 
#define KOOPAS_ANI_RED_UPSIDE_COMEBACK 17 

#define ADJUST_X_TO_RED_CHANGE_DIRECTION 10

//model
#define KOOPAS_GREEN 1
#define KOOPAS_RED 2
#define KOOPAS_GREEN_WING 3



class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;


	ULONGLONG defend_start;

	vector<LPGAMEOBJECT> effects;

	int mario_nx;
	BOOLEAN isTailAttacked = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);



public:
	CKoopas(float x, float y, int model);
	virtual void SetState(int state);

	BOOLEAN isHeld;
	BOOLEAN isDefend;
	BOOLEAN isKicked;
	BOOLEAN isComeback;
	BOOLEAN isUpside;

};