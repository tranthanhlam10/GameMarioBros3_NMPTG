#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 0

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

class CCoin : public CGameObject {
public:
	CCoin(float x, float y) : CGameObject(x, y) {}
	
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsBlocking() { return 0; }

};