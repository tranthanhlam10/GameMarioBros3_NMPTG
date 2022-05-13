#include "Brick.h"

void CBrick::Render()
{
	CAnimationSets* animations = CAnimationSets::GetInstance();
	//animations->Get(ID_ANI_BRICK)->Render(x, y);
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - BRICK_BBOX_WIDTH/2;
	top = y - BRICK_BBOX_HEIGHT/2;
	right = left + BRICK_BBOX_WIDTH;
	bottom = top + BRICK_BBOX_HEIGHT;



}
