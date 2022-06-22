#include "CBrickBreak.h"

CBrickBreak::CBrickBreak(float x, float y) : CGameObject(x, y)
{

	this->ay = BREAK_GRAVTY;
	this->ax = 0;
	this->x = x;
	this->y = y;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_CBB_FROM_TXT));
}

void CBrickBreak::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBrickBreak::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (GetTickCount64() - effect_start > BREAK_EFFECT_TIME_OUT && (state == BREAK_STATE_BOTTOM_RIGHT || state == BREAK_STATE_BOTTOM_LEFT || state == BREAK_STATE_TOP_RIGHT || state == BREAK_STATE_TOP_LEFT)) {
		isDeleted = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBrickBreak::Render()
{
	int ani = ID_ANI_BREAK;

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickBreak::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAK_STATE_TOP_RIGHT:
		vx = BREAK_SPEED_X;
		vy = -BREAK_SPEED_Y_HIGH;
		effect_start = GetTickCount64();
		break;
	case BREAK_STATE_TOP_LEFT:
		vx = -BREAK_SPEED_X;
		vy = -BREAK_SPEED_Y_HIGH;
		effect_start = GetTickCount64();
		break;
	case BREAK_STATE_BOTTOM_LEFT:
		vx = -BREAK_SPEED_X;
		vy = -BREAK_SPEED_Y_LOW;
		effect_start = GetTickCount64();
		break;
	case BREAK_STATE_BOTTOM_RIGHT:
		vx = BREAK_SPEED_X;
		vy = -BREAK_SPEED_Y_LOW;
		effect_start = GetTickCount64();
		break;
	}
}