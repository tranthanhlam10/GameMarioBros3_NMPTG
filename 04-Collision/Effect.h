#pragma once

#include "GameObject.h"
#define SCORE_EFFECT_MAX_HEIGHT 50
#define SCORE_EFFECT_SPEED 0.08f

#define LOAD_EFFECT_FROM_TXT	18

#define ID_ANI_EFFECT_100 0
#define ID_ANI_EFFECT_200 1
#define ID_ANI_EFFECT_400 2
#define ID_ANI_EFFECT_800 3
#define ID_ANI_EFFECT_1000 4
#define ID_ANI_EFFECT_2000 5
#define ID_ANI_EFFECT_4000 6
#define ID_ANI_EFFECT_8000 7
#define ID_ANI_EFFECT_1_UP 8



#define EFFECT_100 1
#define EFFECT_200 2
#define EFFECT_400 3
#define EFFECT_800 4
#define EFFECT_1000 5
#define EFFECT_2000 6
#define EFFECT_4000 7
#define EFFECT_8000 8
#define EFFECT_1_UP 9

class Effect : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;

	BOOLEAN isFinish = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);
	virtual void Render();

public:
	Effect(float x, float y, int model);
	void SetMarioEffect();
};