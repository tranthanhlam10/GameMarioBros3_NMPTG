#include "Leaf.h"

Leaf::Leaf(float x, float y) :CGameObject(x, y)
{

	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
	eType = Type::LEAF;
	SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_LEAF_FROM_TXT));
	minY = y - LEAF_MAX_HEIGHT;
	limitLeft = x;
	limitRight = x + LEAF_MAX_RIGHT;
}

void Leaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + LEAF_BBOX_WIDTH;
	bottom = y + LEAF_BBOX_HEIGHT;
}

void Leaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		y = minY;
		isFall = true;
	}
	if (isFall) {
		vy = LEAF_GRAVITY;
		if (x <= limitLeft)
		{
			x = limitLeft;
			vx = LEAF_SPEED_X;
		}
		if (x >= limitRight)
		{
			x = limitRight;
			vx = -LEAF_SPEED_X;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Leaf::Render()
{
	int ani = -1;
	if (vx > 0) {
		ani = ID_ANI_LEAF_RIGHT;
	}
	else {
		ani = ID_ANI_LEAF_LEFT;
	}

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void Leaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_UP:
		vy = -LEAF_SPEED_UP;
		break;
	}
}
