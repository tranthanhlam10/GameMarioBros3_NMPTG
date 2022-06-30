#include "Pointer.h"

Pointer::Pointer(float x, float y) {
	this->x = x;
	this->y = y;
}

void Pointer::Render() {
	int ani = ARROW_ANI_ID;
	animation_set->at(ani)->Render(x, y);
}