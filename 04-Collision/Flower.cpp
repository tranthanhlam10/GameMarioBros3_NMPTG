#include "Flower.h"

Flower::Flower(float x, float y) :CGameObject(x, y)
{

	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
	
	SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_FLOWER_FROM_TXT));
	minY = y - FLOWER_BBOX_HEIGHT;
}

void Flower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FLOWER_BBOX_WIDTH;
	bottom = y + FLOWER_BBOX_HEIGHT;
}

void Flower::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Flower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if (y <= minY)
	{
		vy = 0;
		y = minY;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Flower::Render()
{
	int ani = ID_ANI_FLOWER;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void Flower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLOWER_STATE_UP:
		vy = -FLOWER_SPEED_UP;
		break;
	}
}

