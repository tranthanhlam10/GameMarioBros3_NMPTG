#include "FirePlant.h"
#include "Mario.h"
#include "PlayScence.h"
#include "FireBall.h"


FirePlant::FirePlant(float x, float y, int model) : CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->model = model;
	this->ax = 0;
	this->ay = 0;
	this->startY = y;
	eType = Type::FIREPLANT;


	if (model == FIRE_PLANT_BIG) {
		this->minY = y - FP_BIG_BBOX_HEIGHT;
	}
	else {
		this->minY = y - FP_SMALL_BBOX_HEIGHT;
	}

	
}

void FirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (model == FIRE_PLANT_BIG) {
		left = x;
		top = y;
		right = left + FP_BBOX_WIDTH;
		bottom = top + FP_BIG_BBOX_HEIGHT;
	}
	else {
		left = x;
		top = y;
		right = left + FP_BBOX_WIDTH;
		bottom = top + FP_SMALL_BBOX_HEIGHT;
	}

}

void FirePlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void FirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	//if (state == ENEMY_STATE_IS_FIRE_ATTACKED || state == ENEMY_STATE_IS_TAIL_ATTACKED) {
	//	isDeleted = true;
	//}

	if (y <= minY) {
		y = minY;
		down_start = GetTickCount64();
		startShoot = true;
	}
	else if (y >= startY) {
		y = startY;
		up_start = GetTickCount64();
		startDown = true;
	}

	if (GetTickCount64() - up_start > FPP_UP_TIME_OUT && startShoot) {
		PlantShootFire();
		startShoot = false;
		vy = FPP_SPEED;
		up_start = 0;
	}

	if (GetTickCount64() - down_start > FPP_DOWN_TIME_OUT && startDown && (GetMarioSafeZone() == 0)) {
		startDown = false;
		vy = -FPP_SPEED;
		down_start = 0;
	}

	for (size_t i = 0; i < TotalFire.size(); i++)
	{
		TotalFire[i]->Update(dt, coObjects);
	}
	GetMarioRangeCurrent();
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FirePlant::Render()
{
	int ani = ID_ANI_FP_LEFT_BOTTOM;
	if (startShoot)
	{
		if (isBottom) {
			if (model == FIRE_PLANT_BIG) {
				if (nx > 0) {
					ani = ID_ANI_FP_RIGHT_BOTTOM_SHOOT;
				}
				else {
					ani = ID_ANI_FP_LEFT_BOTTOM_SHOOT;
				}
			}
			else {
				if (nx > 0) {
					ani = ID_ANI_FP_SMALL_RIGHT_BOTTOM_SHOOT;
				}
				else {
					ani = ID_ANI_FPP_SMALL_LEFT_BOTTOM_SHOOT;
				}
			}
		}
		else {
			if (model == FIRE_PLANT_BIG) {
				if (nx > 0) {
					ani = ID_ANI_FP_RIGHT_TOP_SHOOT;
				}
				else {
					ani = ID_ANI_FP_LEFT_TOP_SHOOT;
				}
			}
			else {
				if (nx > 0) {
					ani = ID_ANI_FP_SMALL_RIGHT_TOP_SHOOT;
				}
				else {
					ani = ID_ANI_FP_SMALL_LEFT_TOP_SHOOT;
				}
			}
		}
	}
	else
	{
		if (isBottom) {
			if (model == FIRE_PLANT_BIG) {
				if (nx > 0) {
					ani = ID_ANI_FP_RIGHT_BOTTOM;
				}
				else {
					ani = ID_ANI_FP_LEFT_BOTTOM;
				}
			}
			else {
				if (nx > 0) {
					ani = ID_ANI_FP_SMALL_RIGHT_BOTTOM;
				}
				else {
					ani = ID_ANI_FP_SMALL_LEFT_BOTTOM;
				}
			}
		}
		else {
			if (model == FIRE_PLANT_BIG) {
				if (nx > 0) {
					ani = ID_ANI_FP_RIGHT_TOP;
				}
				else {
					ani = ID_ANI_FP_LEFT_TOP;
				}
			}
			else {
				if (nx > 0) {
					ani = ID_ANI_FP_SMALL_RIGHT_TOP;
				}
				else {
					ani = ID_ANI_FP_SMALL_LEFT_TOP;
				}
			}
		}
	}

	for (int i = 0; i < TotalFire.size(); i++)
	{
		TotalFire[i]->Render();
	}

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void FirePlant::GetMarioRangeCurrent()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetX() < this->x && mario->GetY() < this->y)
	{
		if (this->x - mario->GetX() < DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO)
		{
			isBottom = false;
			isFar = false;
			nx = -1;
		}
		if (this->x - mario->GetX() >= DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO)
		{
			isBottom = false;
			isFar = true;
			nx = -1;
		}
	}
	if (mario->GetX() < this->x && mario->GetY() > this->y)
	{
		if (this->x - mario->GetX() < DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO)
		{
			isBottom = true;
			isFar = false;
			nx = -1;
		}
		if (this->x - mario->GetX() > DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO)
		{
			isBottom = true;
			isFar = true;
			nx = -1;
		}

	}
	if (mario->GetX() > this->x && mario->GetY() < this->y)
	{
		if (this->x - mario->GetX() < DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO)
		{
			isBottom = false;
			isFar = false;
			nx = 1;
		}
		if (this->x - mario->GetX() >= DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO)
		{
			isBottom = false;
			isFar = true;
			nx = 1;
		}
	}
	if (mario->GetX() > this->x && mario->GetY() > this->y)
	{
		if (this->x - mario->GetX() < DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO)
		{
			isBottom = true;
			isFar = false;
			nx = 1;
		}
		if (this->x - mario->GetX() >= DISTANCE_SHOOT_FIRE_ACCRODING_TO_MARIO)
		{
			isBottom = true;
			isFar = true;
			nx = 1;
		}
	}
}



void FirePlant::PlantShootFire()
{
	FireBall* fireBall = new FireBall(x, y - ADJUST_FPP_SHOOT_FIRE_BALL_HEIGHT);
	int directionYFireball = 0;
	fireBall->SetDirectionX(nx);

	if (isBottom) {
		fireBall->SetDirectionY(1);
		if (isFar) {
			fireBall->SetState(FIRE_BALL_STATE_FPP_SHOOT_FAR);
		}
		else {
			fireBall->SetState(FIRE_BALL_STATE_FPP_SHOOT_NEAR);
		}
	}
	else {
		fireBall->SetDirectionY(-1);
		if (isFar) {
			fireBall->SetState(FIRE_BALL_STATE_FPP_SHOOT_FAR);
		}
		else {
			fireBall->SetState(FIRE_BALL_STATE_FPP_SHOOT_NEAR);
		}
	}
	TotalFire.push_back(fireBall);
}

int FirePlant::GetMarioSafeZone()
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetX() < this->x)
	{
		if (this->x - mario->GetX() <= DISTANCE_SAFE_ZONE)
		{
			return 1;
		}
	}
	if (mario->GetX() > this->x)
	{
		if (mario->GetX() - this->x <= DISTANCE_SAFE_ZONE)
		{
			return 0;
		}
	}
	return 0;
}
