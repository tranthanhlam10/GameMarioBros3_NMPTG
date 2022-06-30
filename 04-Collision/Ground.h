#pragma once

#include "GameObject.h"

#define LOAD_GROUND_FROM_TXT 2
#define GROUND_ANI	0
class Ground : public CGameObject
{
public:
	Ground(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	//~Ground();
};