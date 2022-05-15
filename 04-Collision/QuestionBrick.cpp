#include "QuestionBrick.h"
#include "PlayScence.h"
#include "QuestionBrickCoin.h"
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

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetLevel() == MARIO_LEVEL_SMALL)
	{
		left = x;
		top = y;
		right = x + QUESTION_BRICK_BBOX_WIDTH;
		bottom = y + QUESTION_BRICK_BBOX_HEIGHT;
	}
	else {
		left = x;
		top = y;
		right = x + QUESTION_BRICK_BBOX_WIDTH;
		bottom = y + QUESTION_BRICK_BBOX_HEIGHT + 4;
	}
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

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (y <= minY)
	{
		vy = QUESTION_BRICK_SPEED_DOWN;

	}
	if (y > startY)
	{
		y = startY;
		vy = 0;
		isEmpty = true;
		isUnbox = true;
	}

	if (isUnbox)
	{
		QuestionBrickCoin* QBcoin = new  QuestionBrickCoin(x, y);
		QBcoin->SetState(QB_COIN_STATE_UP);
		//scene->objects.insert(scene->objects.begin() + 1,QBcoin); co the la do minh tile sai ??
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CQuestionBrick::Render()
{
	int ani = ID_ANI_QUESTION_BRICK;

	if (isEmpty) {
		ani = ID_ANI_QUESTION_BRICK_EMPTY;
	}

	animation_set->at(ani)->Render(x, y);
	/*RenderBoundingBox();*/
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