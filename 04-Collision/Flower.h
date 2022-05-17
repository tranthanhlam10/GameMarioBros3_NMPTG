#pragma once
#include "GameObject.h"

#define LOAD_FLOWER_FROM_TXT 6
#define FLOWER_BBOX_WIDTH 16
#define FLOWER_BBOX_HEIGHT 16
#define ID_ANI_FLOWER 0	

#define FLOWER_STATE_UP 2002
#define FLOWER_SPEED_UP 0.1f

class Flower : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

public:
	Flower(float x, float y);
	virtual void SetState(int state);
};

