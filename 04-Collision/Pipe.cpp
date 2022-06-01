#include "Pipe.h"
#include "Utils.h"
#include "debug.h"
#include "Mario.h"
#include "PlayScence.h"


CPipe::CPipe(float x, float y, int model) : CGameObject(x, y) {

	this->x = x;
	this->y = y;
	this->model = model;
	SetType(Type::OBJECT);
}

void CPipe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	   CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	
	   if (mario->GetLevel() == MARIO_LEVEL_RACOON) {

		   left = x - PIPE_BBOX_WIDTH / 2 + (PIPE_BBOX_WIDTH / 8); 

		   right = left + PIPE_BBOX_WIDTH + (PIPE_BBOX_WIDTH/8) + (PIPE_BBOX_WIDTH / 16);

		   if (model == PIPE_LONG) {
			   top = y - PIPE_LONG_BBOX_HEIGHT / 2 + (PIPE_LONG_BBOX_HEIGHT /4);
			   bottom = top + PIPE_LONG_BBOX_HEIGHT;
		   }	
		   else if (model == PIPE_MEDIUM) {
			   top = y - PIPE_MEDIUM_BBOX_HEIGHT / 2 + (PIPE_MEDIUM_BBOX_HEIGHT / 4);
			   bottom = top + PIPE_MEDIUM_BBOX_HEIGHT;
		   }

	   }
	   else {

		   left = x - PIPE_BBOX_WIDTH / 2 + PIPE_TOP_PIXEL;

		   right = left + PIPE_BBOX_WIDTH;

		   if (model == PIPE_LONG) {
			   top = y - PIPE_LONG_BBOX_HEIGHT / 2 + (PIPE_LONG_BBOX_HEIGHT / 6);
			   bottom = top + PIPE_LONG_BBOX_HEIGHT;
		   }
		   else if (model == PIPE_MEDIUM) {
			   top = y - PIPE_MEDIUM_BBOX_HEIGHT / 2 + (PIPE_MEDIUM_BBOX_HEIGHT / 4);
			   bottom = top + PIPE_MEDIUM_BBOX_HEIGHT;
		   }
	   }
}


void CPipe::Render()
{
	int ani = ID_ANI_PIPE_LONG;

	if (model == PIPE_MEDIUM) {
		ani = ID_ANI_PIPE_MEDIUM;
	}

	animation_set->at(ani)->Render(x , y);
	//RenderBoundingBox();
}