#include "Pipe.h"

CPipe::CPipe(float x, float y, int model) : CGameObject(x, y) {

	this->x = x;
	this->y = y;
	this->model = model;
	eType = Type::PIPE;
}

void CPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	/*left = x - PIPE_BBOX_WIDTH / 2;
	right = left + PIPE_BBOX_WIDTH;

	if (model == PIPE_LONG) {
		top = y - PIPE_LONG_BBOX_HEIGHT / 2;
		bottom = top + PIPE_LONG_BBOX_HEIGHT;
	}
	else if (model == PIPE_MEDIUM) {
		top = y - PIPE_MEDIUM_BBOX_HEIGHT / 2;
		bottom = top + PIPE_MEDIUM_BBOX_HEIGHT;
	}*/

	left = this->x;
	top = y;
	right = this->x + PIPE_BBOX_WIDTH;
	if (model == PIPE_MEDIUM)
	{
		bottom = y + PIPE_MEDIUM_BBOX_HEIGHT;
	}
	if (model == PIPE_LONG)
	{
		bottom = y + PIPE_LONG_BBOX_HEIGHT;
	}
}


void CPipe::Render()
{
	int ani = ID_ANI_PIPE_LONG;

	if (model == PIPE_MEDIUM) {
		ani = ID_ANI_PIPE_MEDIUM;
	}

	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}