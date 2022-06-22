#pragma once
#include "GameObject.h"


#define LOAD_PBUTTON_FROM_TXT 17
#define P_BUTTON_ANI 0
#define P_BUTTON_ANI_IS_PRESSED 1

#define	P_BUTTON_BBOX_WIDTH 16
#define P_BUTTON_BBOX_HEIGHT 16

#define P_BUTTON_IS_PRESSED_BBOX_HEIGHT 11

class PButton : public CGameObject
{
protected:
	float ax;
	float ay;

	BOOLEAN isPressed = false;
	BOOLEAN isCoinBrickTransform = false;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual int IsBlocking();

public:
	PButton(float x, float y);
	void SetIsPressed(BOOLEAN isPressed) { this->isPressed = isPressed; }
	void SetCoinBrickTransform(BOOLEAN isCoinBrickTransform) { this->isCoinBrickTransform = isCoinBrickTransform; }
};

