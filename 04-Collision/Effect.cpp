
#include "PlayScence.h"
#include "Effect.h"
#include "Mario.h"	

Effect::Effect(float x, float y, int model) : CGameObject(x, y)
{

	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
	this->model = model;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_EFFECT_FROM_TXT));
	minY = y - SCORE_EFFECT_MAX_HEIGHT;
	this->vy = -SCORE_EFFECT_SPEED;
}

void Effect::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Effect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		isDeleted = true;
	}
	if (isDeleted) {
		SetMarioEffect();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void Effect::Render()
{
	int ani = ID_ANI_EFFECT_100;
	switch (model) {
	case EFFECT_100:
		ani = ID_ANI_EFFECT_100;
		break;
	case EFFECT_200:
		ani = ID_ANI_EFFECT_200;
		break;
	case EFFECT_400:
		ani = ID_ANI_EFFECT_400;
		break;
	case EFFECT_800:
		ani = ID_ANI_EFFECT_800;
		break;
	case EFFECT_1000:
		ani = ID_ANI_EFFECT_1000;
		break;
	case EFFECT_2000:
		ani = ID_ANI_EFFECT_2000;
		break;
	case EFFECT_4000:
		ani = ID_ANI_EFFECT_4000;
		break;
	case EFFECT_8000:
		ani = ID_ANI_EFFECT_8000;
		break;
	case EFFECT_1_UP:
		ani = ID_ANI_EFFECT_1_UP;
	}

	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void Effect::SetMarioEffect() {
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (model) {
	case EFFECT_100:
		mario->SetScore(mario->GetScore() + 100);
		break;
	case EFFECT_200:
		mario->SetScore(mario->GetScore() + 200);
		break;
	case EFFECT_400:
		mario->SetScore(mario->GetScore() + 400);
		break;
	case EFFECT_800:
		mario->SetScore(mario->GetScore() + 800);
		break;
	case EFFECT_1000:
		mario->SetScore(mario->GetScore() + 1000);
		break;
	case EFFECT_2000:
		mario->SetScore(mario->GetScore() + 2000);
		break;
	case EFFECT_4000:
		mario->SetScore(mario->GetScore() + 4000);
		break;
	case EFFECT_8000:
		mario->SetScore(mario->GetScore() + 8000);
		break;
	case EFFECT_1_UP:
		mario->SetHealth(mario->GetHealth() + 1);
	}
}
