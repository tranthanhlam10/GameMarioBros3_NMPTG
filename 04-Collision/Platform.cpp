#include "Platform.h"


Platform::Platform()
{
	eType = Type::COIN;
}

void Platform::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y  ;
	right = x + BRICK_BBOX_WIDTH;
	bottom = y + BRICK_BBOX_HEIGHT;
}

void Platform::Render()
{
	//RenderBoundingBox();
}
