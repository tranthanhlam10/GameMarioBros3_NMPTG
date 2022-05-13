#pragma once
#include "GameObject.h"

#define PIPE_BBOX_WIDTH 32
#define PIPE_MEDIUM_BBOX_HEIGHT 32
#define PIPE_LONG_BBOX_HEIGHT 48

#define ID_ANI_PIPE_LONG 0
#define ID_ANI_PIPE_MEDIUM 1
#define PIPE_LONG 1
#define PIPE_MEDIUM 2
class CPipe : public CGameObject
{
public:
	CPipe(float x, float y, int model);
	void Render();
	void Update(DWORD dt) {}

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

