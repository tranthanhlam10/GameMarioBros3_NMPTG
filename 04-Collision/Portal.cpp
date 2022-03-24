#include "Portal.h"


CPortal::CPortal(float l, float t, float r, float b, float scene_id)
{
	this->scene_id = scene_id;
	this->x = l;
	this->y = t;
	width = r - l + 1;
	height = b - t + 1;
}

void CPortal::Render()
{
	//RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}