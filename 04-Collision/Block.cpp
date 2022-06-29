#include "Block.h"

void Block::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - BLOCK_OBJ_BBOX_WIDTH / 2;
	right = left + BLOCK_OBJ_BBOX_WIDTH;
	top = y - BLOCK_OBJ_BBOX_HEIGHT / 2;
	bottom = top + BLOCK_OBJ_BBOX_HEIGHT;
}

void Block::Render()
{
	//RenderBoundingBox();
}