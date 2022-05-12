#include "QuestionBrick.h"
#include "PlayScence.h"





CQuestionBrick::CQuestionBrick(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;
	eType = Type::QUESTIONBRICK;
	this->ay = 0;
	this->ax = 0;
	this->minY = y - QUESTION_BRICK_BBOX_HEIGHT;
	this->startY = y;
}

void CQuestionBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + QUESTION_BRICK_BBOX_WIDTH;
	bottom = y + QUESTION_BRICK_BBOX_HEIGHT;
}

void CQuestionBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

}


void CQuestionBrick::Render()
{
	int ani = ID_ANI_QUESTION_BRICK;

	if (isEmpty) {
		ani = ID_ANI_QUESTION_BRICK_EMPTY;
	}

	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CQuestionBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QUESTION_BRICK_STATE_UP:
		vy = -QUESTION_BRICK_SPEED_UP;
		break;
	}
}