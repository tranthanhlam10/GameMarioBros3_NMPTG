#include "Three.h"

Three::Three(float x, float y) {
	this->x = x;
	this->y = y;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_THREE_FROM_TXT));
}
void Three::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}
void Three::Render() {
	int ani = THREE_ANI;
	animation_set->at(ani)->Render(x, y);
}