#include "Plant.h"
#include "Mario.h"
#include "PlayScence.h"


Plant::Plant(float x, float y, float model) :CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->ax = 0;
	this->ay = 0;
	this->startY = y;
	this->minY = y - PIRANHA_PLANT_BBOX_HEIGHT;
	eType = Type::PLANT;
	this->model = model;
	
}

void Plant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHA_PLANT_BBOX_WIDTH / 2;
	top = y - PIRANHA_PLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHA_PLANT_BBOX_WIDTH;
	bottom = top + PIRANHA_PLANT_BBOX_HEIGHT;
}

void Plant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Plant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	/*if (state == ENEMY_STATE_IS_FIRE_ATTACKED || state == ENEMY_STATE_IS_TAIL_ATTACKED) {
		isDeleted = true;
	}*/

	vy += ay * dt;
	vx += ax * dt;

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (y <= minY) {
		y = minY;
		down_start = GetTickCount64();
		startUp = true;
	}
	else if (y >= startY) {
		y = startY;
		up_start = GetTickCount64();
		startDown = true;
	}

	if (GetTickCount64() - up_start > PIRANHA_PLANT_UP_TIME_OUT && startUp) {
		startUp = false;
		SetState(PIRANHA_STATE_DOWN);
		up_start = 0;
	}

	if (GetTickCount64() - down_start > PIRANHA_PLANT_DOWN_TIME_OUT && startDown ) {
		startDown = false;
		SetState(PIRANHA_STATE_UP);
		down_start = 0;
	}


	if (mario->GetX() < this->x) {
		if (this->x - mario->GetX() <= DISTANCE_MARIO_SAFE_ZONE) {
			isMarioSafeZone = true;
		}
		else {
			isMarioSafeZone = false;
		}
	}
	else {
		if (mario->GetX() - this->x <= DISTANCE_MARIO_SAFE_ZONE) {
			isMarioSafeZone = true;
		}
		else {
			isMarioSafeZone = false;
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Plant::Render()
{
	int ani = ID_ANI_PIRANHA_PLANT;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void Plant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHA_STATE_DOWN:
		vy = PIRANHA_SPEED;
		break;
	case PIRANHA_STATE_UP:
		vy = -PIRANHA_SPEED;
		break;
	}
}