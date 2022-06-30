#pragma once
#include "GameObject.h"

#define ARROW_ANI_ID 0

class Pointer : public CGameObject
{
public:
	Pointer(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
	
};

