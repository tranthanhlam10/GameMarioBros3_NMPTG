#pragma once


#include "GameObject.h"

#define LOAD_THREE_FROM_TXT	3
#define THREE_ANI	0

class Three : public CGameObject
{
public:
	Three(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

};