#include "Koopas.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScence.h"
#include "Goomba.h"
#include "QuestionBrick.h"
#include "ColorBlock.h"


CKoopas::CKoopas(float x, float y, int model) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;

	
	defend_start = -1;
	isHeld = false;
	
	this->model = model;
	if (model == KOOPAS_GREEN_WING) {
		SetState(KOOPAS_STATE_JUMP);
	}
	else {
		SetState(KOOPAS_STATE_WALKING);
	}

	SetType(Type::ENEMY);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDefend || isUpside) {

		left = x ;
		top = y;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DEFEND;

	}
	else {
		left = x ;
		top = y - KOOPAS_ADJUST_PX;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

int CKoopas::IsCollidable()
{
	if (state == ENEMY_STATE_IS_FIRE_ATTACKED || state == ENEMY_STATE_IS_KOOPAS_ATTACKED || state == ENEMY_STATE_IS_TAIL_ATTACKED) {
		return 0;
	}
	else {
		return 1;
	}
}
void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		vy = 0;

		if (isTailAttacked) {
			SetState(KOOPAS_STATE_UPSIDE);
			vy = -KOOPAS_BOUNCE_SPEED;
			isTailAttacked = false;
		}
		else {
			if (model == KOOPAS_GREEN_WING && state == KOOPAS_STATE_JUMP) {
				vy = -KOOPAS_WING_JUMP_SPEED;
				ay = KOOPAS_WING_GRAVITY;
			}
		}
	}
	else if (e->nx != 0)
	{
		if (e->obj->GetType() == OBJECT ) {
			vx = -vx;	
		}
	}

	if (e->obj->GetType() == ENEMY) {
		if (e->obj->GetState() != ENEMY_STATE_IS_KOOPAS_ATTACKED) {
			if (state == KOOPAS_STATE_IS_KICKED) {
				e->obj->SetState(ENEMY_STATE_IS_KOOPAS_ATTACKED);
			}
		}
	}

	if (dynamic_cast<CColorBlock*>(e->obj))
		OnCollisionWithColorBlock(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	
}


void CKoopas::OnCollisionWithColorBlock(LPCOLLISIONEVENT e)
{
	CColorBlock* block = dynamic_cast<CColorBlock*>(e->obj);

	if (e->ny < 0) 
		if (state == KOOPAS_STATE_WALKING && model == KOOPAS_RED) {
			if (x <= block->GetX() )
			{
				vy = 0;
				vx = KOOPAS_WALKING_SPEED;
			}
			else if (x >= block->GetX() + RED_KOOPAS_CB_PX) {
				vy = 0;
				vx = -KOOPAS_WALKING_SPEED;
			}
		}
	
}

void CKoopas::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);

	if (e->nx != 0 && !questionBrick->isEmpty) {
		if (state == KOOPAS_STATE_IS_KICKED) {
			questionBrick->SetState(QUESTION_BRICK_STATE_UP);
		}
	}

}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->isHoldingTurtle && isHeld) {
		if (mario->GetDirection() > 0) {
			this->x = mario->GetX() + ADJUST_POSITION_KOOPAS_HELD;
			this->y = mario->GetY();
		}
		else {
			this->x = mario->GetX() - ADJUST_POSITION_KOOPAS_HELD;
			this->y = mario->GetY();
		}
		vy = 0;
	}
	else {
		if (this->isHeld) {
			ay = KOOPAS_GRAVITY;
			SetState(KOOPAS_STATE_IS_KICKED);
		}
	}


	if (GetTickCount64() - defend_start > KOOPAS_COMBACK_START && (isDefend || isUpside) && !isKicked) {
		isComeback = true;
	}

	
	if (GetTickCount64() - defend_start > KOOPAS_DEFEND_TIMEOUT && (isDefend || isUpside) && !isKicked) {


		SetState(KOOPAS_STATE_WALKING);
		defend_start = -1;
		vy = -KOOPAS_COMBACK_HEIGHT_ADJUST;

		if (mario->isHoldingTurtle) {
			mario->isHoldingTurtle = false;
			if (mario->GetLevel() > MARIO_LEVEL_SMALL)
			{
				mario->LevelDown();
				mario->StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	
	int ani = -1;
	if (model == KOOPAS_RED)
	{

		if (state == ENEMY_STATE_IS_FIRE_ATTACKED || state == ENEMY_STATE_IS_KOOPAS_ATTACKED || state == ENEMY_STATE_IS_TAIL_ATTACKED) {
			ani = KOOPAS_ANI_RED_IS_UPSIDE;
		}
		if (vx > 0)
		{
			if (state == KOOPAS_STATE_WALKING)
			{
				ani = KOOPAS_ANI_RED_WALKING_RIGHT;
			}
			else if (isKicked)
			{
				if (isDefend)
				{
					ani = KOOPAS_ANI_RED_IS_KICKED;
				}
				else if (isUpside)
				{
					ani = KOOPAS_ANI_RED_UPSIDE_ISKICKED;
				}
			}
		}
		else
		{
			if (state == KOOPAS_STATE_WALKING)
			{
				ani = KOOPAS_ANI_RED_WALKING_LEFT;
			}
			else if (isKicked)
			{
				if (isDefend)
				{
					ani = KOOPAS_ANI_RED_IS_KICKED;
				}
				else if (isUpside)
				{
					ani = KOOPAS_ANI_RED_UPSIDE_ISKICKED;
				}
			}
		}
		if (!isKicked)
		{
			if (isDefend)
			{
				if (isComeback)
				{
					ani = KOOPAS_ANI_RED_COMEBACK;
				}
				else
				{
					ani = KOOPAS_ANI_RED_DEFEND;
				}
			}
			else if (isUpside)
			{
				if (isComeback)
				{
					ani = KOOPAS_ANI_RED_UPSIDE_COMEBACK;
				}
				else
				{
					ani = KOOPAS_ANI_RED_IS_UPSIDE;
				}
			}
		}
	}

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		vy = 0;
		ay = KOOPAS_GRAVITY;
		isComeback = false;
		isDefend = false;
		isUpside = false;
		isKicked = false;
		isHeld = false;
		break;
	case KOOPAS_STATE_DEFEND:
		isDefend = true;
		isComeback = false;
		isKicked = false;
		isUpside = false;
		defend_start = GetTickCount64();
		vx = 0;
		break;
	case KOOPAS_STATE_UPSIDE:
		isUpside = true;
		isDefend = false;
		isComeback = false;
		isKicked = false;
		defend_start = GetTickCount64();
		vx = 0;
		break;
	case KOOPAS_STATE_IS_KICKED:
		isKicked = true;
		isHeld = false;
		vx = mario->GetDirection() * KOOPAS_IS_KICKED_SPEED;
		break;
	case KOOPAS_STATE_JUMP:
		vx = KOOPAS_RED_WING_SPEED_X;
		isComeback = false;
		isDefend = false;
		isUpside = false;
		isKicked = false;
		break;
	case ENEMY_STATE_IS_TAIL_ATTACKED:
		ay = KOOPAS_GRAVITY;
		vy = -KOOPAS_SPEED_Y_IS_TAIL_ATTACKED;
		vx = mario->GetDirection() * KOOPAS_SPEED_X_IS_TAIL_ATTACKED;
		isTailAttacked = true;
		break;
	case ENEMY_STATE_IS_FIRE_ATTACKED:
		ay = KOOPAS_GRAVITY;
		vy = -KOOPAS_SPEED_Y_IS_FIRE_ATTACKED;
		vx = 0;
		break;
	case ENEMY_STATE_IS_KOOPAS_ATTACKED:
		ay = KOOPAS_GRAVITY;
		vx = 0;
		break;
	
	}

}
