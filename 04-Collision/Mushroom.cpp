#include "Mushroom.h"
#include "QuestionBrick.h"
#include "Leaf.h"
#include "MushRoom.h"

MushRoom::MushRoom(float x, float y, int model) : CGameObject(x, y)
{
	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
	
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_MUSHROOM_FROM_TXT));
	minY = y - MUSHROOM_BBOX_HEIGHT;
	this->model = model;
}

void MushRoom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x ;
	top = y ;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void MushRoom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void MushRoom::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void MushRoom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		SetState(MUSHROOM_STATE_RUN);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void MushRoom::Render()
{
	int ani = -1;

	if (model == GREEN_MUSHROOM) {
		ani = ID_ANI_GREEN_MUSHROOM;
	}
	else {
		ani = ID_ANI_RED_MUSHROOM;
	}

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
	
}

void MushRoom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_UP:
		vy = -MUSHROOM_SPEED_UP;
		break;
	case MUSHROOM_STATE_RUN:
		vx = MUSHROOM_RUN_SPEED;
		ay = MUSHROOM_GRAVITY;
		break;
	}
}
