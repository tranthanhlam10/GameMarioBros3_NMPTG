#include "Pipe.h"
#include "Utils.h"
#include "debug.h"

CPipe::CPipe(float x, float y, int model) : CGameObject(x, y) {

	this->x = x;
	this->y = y;
	this->model = model;
	eType = Type::PIPE;
}

void CPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = x + PIPE_BBOX_WIDTH;
	top = y;
	if (model == PIPE_LONG) {	
		bottom = top + PIPE_LONG_BBOX_HEIGHT;
	}
	else if (model == PIPE_MEDIUM) {
		bottom = top + PIPE_MEDIUM_BBOX_HEIGHT;
	}
}


void CPipe::Render()
{
	int ani = ID_ANI_PIPE_LONG;

	if (model == PIPE_MEDIUM) {
		ani = ID_ANI_PIPE_MEDIUM;
	}

	animation_set->at(ani)->Render(x , y);
	RenderBoundingBox();
}