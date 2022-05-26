#include "Koopas.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScence.h"
#include "Goomba.h"
#include "QuestionBrick.h"
#include "ColorBlock.h"
#include "debug.h"


CKoopas::CKoopas(float x, float y, int model) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->model = model;
	//eType = Type::KOOPAS;
	defend_start = -1;
	isHeld = false;
	if (model == KOOPAS_GREEN_WING) {
		SetState(KOOPAS_STATE_JUMP);
	}
	else {
		SetState(KOOPAS_STATE_WALKING);
	}

	
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDefend || isUpside) {

		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_DEFEND / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DEFEND;

	}
	else {
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


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

	// start animation comeback

	if (GetTickCount64() - defend_start > KOOPAS_COMBACK_START && (isDefend || isUpside) && !isKicked) {
		isComeback = true;
	}

	// end defend and start walking
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

	for (size_t i = 0; i < effects.size(); i++)
	{
		effects[i]->Update(dt, coObjects);
		if (effects[i]->isDeleted) {
			effects.erase(effects.begin() + i);
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int ani= KOOPAS_ANI_WALKING_RIGHT;

	if (model == KOOPAS_GREEN_WING) {
		if (vx > 0) {
			ani = KOOPAS_ANI_GREEN_WING_RIGHT;
		}
		else {
			ani = KOOPAS_ANI_GREEN_WING_LEFT;
		}
	}

	if (model == KOOPAS_GREEN || model == KOOPAS_GREEN_WING)
	{
		if (vx > 0)
		{
			if (state == KOOPAS_STATE_WALKING)
			{
				ani = KOOPAS_ANI_WALKING_RIGHT;
			}
			else if (isKicked)
			{
				if (isDefend)
				{
					ani = KOOPAS_ANI_IS_KICKED;
				}
				else if (isUpside)
				{
					ani = KOOPAS_ANI_UPSIDE_ISKICKED;
				}
			}
		}
		else
		{
			if (state == KOOPAS_STATE_WALKING)
			{
				ani = KOOPAS_ANI_WALKING_LEFT;
			}
			else if (isKicked)
			{
				if (isDefend)
				{
					ani = KOOPAS_ANI_IS_KICKED;
				}
				else if (isUpside)
				{
					ani = KOOPAS_ANI_IS_KICKED;
				}
			}
		}
		if (!isKicked)
		{
			if (isDefend)
			{
				if (isComeback)
				{
					ani = KOOPAS_ANI_COMEBACK;
				}
				else
				{
					ani = KOOPAS_ANI_DEFEND;
				}
			}
			else if (isUpside)
			{
				if (isComeback)
				{
					ani = KOOPAS_ANI_UPSIDE_COMEBACK;
				}
				else
				{
					ani = KOOPAS_ANI_IS_UPSIDE;
				}
			}
		}
	}
	else if (model == KOOPAS_RED)
	{
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

	/*for (int i = 0; i < effects.size(); i++)
	{
		effects[i]->Render();
	}*/

	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
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
	}

}
