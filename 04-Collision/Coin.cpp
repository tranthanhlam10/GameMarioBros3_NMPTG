#include "Coin.h"
void CCoin::Render()
{
	int ani = ID_ANI_COIN;
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& left, float& top, float& right, float& bot)
{
	left = x - COIN_BBOX_WIDTH / 2;
	top = y - COIN_BBOX_HEIGHT / 2;
	right = left + COIN_BBOX_WIDTH;
	bot = top + COIN_BBOX_HEIGHT;
}