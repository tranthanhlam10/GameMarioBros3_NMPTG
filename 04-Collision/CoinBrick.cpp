#include "CoinBrick.h"
#include "PlayScence.h"
#include "MushRoom.h"

#include "CBrickBreak.h"

CoinBrick::CoinBrick(float x, float y, int model) :CGameObject(x, y)
{
	this->model = model;

	this->ay = 0;
	this->ax = 0;
	this->minY = y - COIN_BRICK_BBOX_HEIGHT;
	this->startY = y;
	this->startX = x;

	SetType(Type::COINBRICK);
}

void CoinBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + COIN_BRICK_BBOX_WIDTH;
	bottom = top + COIN_BRICK_BBOX_HEIGHT;
}

void CoinBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void CoinBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		vy = COIN_BRICK_SPEED_DOWN;
		if (mario->GetLevel() != MARIO_LEVEL_SMALL) {
			if (model == COIN_BRICK_COIN) {
				isBreak = true;
			}
		}
	}
	if (y > startY)
	{
		y = startY;
		vy = 0;
		if (mario->GetLevel() != MARIO_LEVEL_SMALL) {
			isEmpty = true;
			isUnbox = true;
		}
	}

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isUnbox) {
		if (model == COIN_BRICK_MUSHROOM) {
			MushRoom* mushroom = new MushRoom(x, y, GREEN_MUSHROOM);
			mushroom->SetState(MUSHROOM_STATE_UP);
			scene->objects.insert(scene->objects.begin() + 1, mushroom);
		}
		isUnbox = false;
	}

	if (isBreak) {
		CBrickBreak* breaktopright = new CBrickBreak(x, y);
		breaktopright->SetState(BREAK_STATE_TOP_RIGHT);
		CBrickBreak* breaktopleft = new CBrickBreak(x, y);
		breaktopleft->SetState(BREAK_STATE_TOP_LEFT);
		CBrickBreak* breakbotright = new CBrickBreak(x, y);
		breakbotright->SetState(BREAK_STATE_BOTTOM_RIGHT);
		CBrickBreak* breakbotleft = new CBrickBreak(x, y);
		breakbotleft->SetState(BREAK_STATE_BOTTOM_LEFT);
		scene->objects.insert(scene->objects.begin() + 1, breaktopright);
		scene->objects.insert(scene->objects.begin() + 1, breaktopleft);
		scene->objects.insert(scene->objects.begin() + 1, breakbotright);
		scene->objects.insert(scene->objects.begin() + 1, breakbotleft);
		isDeleted = true;
		isBreak = false;
	}

	if (isTransform && GetTickCount64() - transform_start > COIN_BRICK_COIN_TIME_OUT) {
		SetState(COIN_BRICK_STATE_NORMAL);
		isTransform = false;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


int CoinBrick::IsBlocking() {
	if (state == COIN_BRICK_STATE_TRANSFORM_COIN) {
		return 0;
	}
	else
		return 1;

}

void CoinBrick::Render()
{
	int ani = COIN_ANI_BRICK;

	if (model != COIN_BRICK_COIN) {
		if (isEmpty) {
			ani = COIN_ANI_BRICK_EMPTY;
		}
	}
	else {
		if (isTransform) {
			ani = ID_ANI_COIN_IDLE;
		}
		else {
			ani = COIN_ANI_BRICK;
		}
	}

	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CoinBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN_BRICK_STATE_UP:
		vy = -COIN_BRICK_SPEED_UP;
		break;
	case COIN_BRICK_STATE_TRANSFORM_COIN:
		if (type ==COINBRICK) {
			SetType(Type::COIN);
			transform_start = GetTickCount64();
			isTransform = true;
		}
		break;
	case COIN_BRICK_STATE_NORMAL:
		if (type == COIN) {
			SetType(Type::COINBRICK);
			transform_start = -1;
			isTransform = false;
		}
		break;
	}
}