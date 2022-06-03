#include "TailAttack.h"
#include "QuestionBrick.h"
#include "debug.h"
#include "PlayScence.h"

void TailAttack::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	right = left + width;
	top = y;
	bottom = top + height;
}


void TailAttack::OnCollisionWithQuestionBrick(LPGAMEOBJECT& e)
{
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e);
	if (!questionBrick->isEmpty) {
		questionBrick->SetState(QUESTION_BRICK_STATE_UP);
	}
}

void TailAttack::OnCollisionWithEnemy(LPGAMEOBJECT& e)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	e->SetState(ENEMY_STATE_IS_TAIL_ATTACKED);
}

void TailAttack::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (CCollision::GetInstance()->CheckAABB(this, coObjects->at(i)))
		{
			if (coObjects->at(i)->GetType() == ENEMY) {
				OnCollisionWithEnemy(coObjects->at(i));
			}
			else if (dynamic_cast<CQuestionBrick*>(coObjects->at(i)))
				OnCollisionWithQuestionBrick(coObjects->at(i));
		}
	}

	for (size_t i = 0; i < effects.size(); i++)
	{
		effects[i]->Update(dt, coObjects);
		if (effects[i]->isDeleted) {
			effects.erase(effects.begin() + i);
		}
	}
}

void TailAttack::Render() {
	for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Render();
	}
	//RenderBoundingBox();
}