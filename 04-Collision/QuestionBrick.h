#pragma once
#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16

#define ID_ANI_QUESTION_BRICK 1
#define ID_ANI_QUESTION_BRICK_EMPTY 2


#define QUESTION_BRICK_MAX_HEIGHT 10 
#define QUESTION_BRICK_SPEED_UP 0.1f
#define QUESTION_BRICK_SPEED_DOWN 0.1f

#define QUESTION_BRICK_ITEM 2
#define QUESTION_BRICK_COIN 1

#define QUESTION_BRICK_STATE_UP 100

class CQuestionBrick : public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;
	float startY;



	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);

public:

	CQuestionBrick(float x, float y, int model);
	virtual void SetState(int state);
	BOOLEAN isUnbox = false;
	BOOLEAN isEmpty = false;
	CGameObject* item = NULL;
};