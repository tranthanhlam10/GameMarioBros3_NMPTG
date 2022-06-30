#include "Ground.h"

Ground::Ground(float x, float y) {
	this->x = x;
	this->y = y;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_GROUND_FROM_TXT));
}

void Ground::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}

void Ground::Render() {
	int ani = GROUND_ANI;
	animation_set->at(ani)->Render(x, y);
}