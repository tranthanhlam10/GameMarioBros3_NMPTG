#include "QuestionBrickCoin.h"
#include "PlayScence.h"


QuestionBrickCoin::QuestionBrickCoin(float x, float y) : CGameObject(x, y)
{

	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
	SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_QB_COIN));
	eType = Type::QUESTIONBRICKCOIN;
	minY = y - QB_COIN_MAX_HEIGHT;
	heightFinish = y - HEIGHT_FINISH;
}

void QuestionBrickCoin::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void QuestionBrickCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	
	if (y <= minY)
	{
		y = minY;
		SetState(QB_COIN_STATE_DOWN);
		isFall = true;
	}
	if (y >= heightFinish && isFall)
	{
		isDeleted = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void QuestionBrickCoin::Render()
{
	int ani= ID_ANI_QB_COIN;

	animation_set->at(ani)->Render(x, y);
}

void QuestionBrickCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case QB_COIN_STATE_UP:
		vy = -QB_COIN_SPEED;
		break;
	case QB_COIN_STATE_DOWN:
		vy = QB_COIN_SPEED;
		break;
	}
}
