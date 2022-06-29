
#include "Grass.h"

void Grass::Render()
{
	int ani = ID_ANI_GRASS;
	animation_set->at(ani)->Render(x, y);
}