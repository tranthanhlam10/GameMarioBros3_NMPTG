#include "Hammer.h"

Hammer::Hammer(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->startX = x;
	limitRight = x + HAMMER_WORLD_MAP_LIMIT_WALK;
	SetState(HAMMER_WORLD_MAP_STATE_WALK);
}

void Hammer::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void Hammer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vx += ax * dt;
	vy += ay * dt;

	if (x <= startX) {
		SetState(HAMMER_WORLD_MAP_STATE_WALK);
	}
	if (x >= limitRight)
	{
		SetState(HAMMER_WORLD_MAP_STATE_WALK_LEFT);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Hammer::Render()
{
	int ani = ID_ANI_HAMMER_WORLD_MAP_WALK_RIGHT;
	if (vx < 0) {
		ani = ID_ANI_HAMMER_WORLD_MAP_WALK_LEFT;
	}
	else {
		ani = ID_ANI_HAMMER_WORLD_MAP_WALK_RIGHT;
	}
	animation_set->at(ani)->Render(x, y);
}

void Hammer::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case HAMMER_WORLD_MAP_STATE_WALK:
		vx = HAMMER_WORLD_MAP_WALK_SPEED;
		break;
	case HAMMER_WORLD_MAP_STATE_WALK_LEFT:
		vx = -HAMMER_WORLD_MAP_WALK_SPEED;
		break;
	}
}