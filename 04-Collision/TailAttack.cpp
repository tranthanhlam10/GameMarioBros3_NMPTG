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

void TailAttack::OnCollisionWithCoinBrick(LPGAMEOBJECT& e)
{
	CoinBrick* coinBrick = dynamic_cast<CoinBrick*>(e);
	if (!coinBrick->isEmpty) {
		coinBrick->SetBreak(true);
	}
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
			else if (dynamic_cast<CoinBrick*>(coObjects->at(i)))
				OnCollisionWithCoinBrick(coObjects->at(i));
		}
	}
}

void TailAttack::Render() {

	//RenderBoundingBox();
}