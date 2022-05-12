#include "ColorBlock.h"

#include "Mario.h"
#include "PlayScence.h"
#include "debug.h"

CColorBlock::CColorBlock(float x, float y, float width, float height) : CGameObject(x, y) {

	this->width = width;
	this->height = height;
}

void CColorBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y +1 ;
}