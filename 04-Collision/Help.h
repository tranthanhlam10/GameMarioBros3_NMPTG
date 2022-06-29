#pragma once

#include "GameObject.h"
#define ID_ANI_HELP_WORLD_MAP 0

class Help : public CGameObject
{
public:
	Help(float x, float y) : CGameObject(x, y) {}
	virtual void Render();
	void Update(DWORD dt) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) { left = top = right = bottom = 0; }
};

