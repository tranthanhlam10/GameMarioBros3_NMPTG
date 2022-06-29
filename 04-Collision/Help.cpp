#include "Help.h"

void Help::Render() {
	int ani = ID_ANI_HELP_WORLD_MAP;
	animation_set->at(ani)->Render(x, y);
}