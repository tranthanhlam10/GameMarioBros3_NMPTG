#include "FireBall.h"
#include "Mario.h"
#include "PlayScence.h"

FireBall::FireBall(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = FIRE_BALL_GRAVITY;
	eType = Type::FIREBALL;
	this->SetAnimationSet(CAnimationSets::GetInstance()->Get(LOAD_FIREBALL_FROM_TXT));
	this->x = x;
	this->y = y;

}

void FireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y ;
	right = left + FIRE_BALL_BBOX_WIDTH;
	bottom = top + FIRE_BALL_BBOX_HEIGHT;
}

void FireBall::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void FireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (e->ny < 0 && state == FIRE_BALL_STATE_MARIO_SHOOT)
	{
		vy = -FIRE_BALL_BOUNCE_SPEED;

	}
	else if (e->ny > 0) {
		ay = FIRE_BALL_GRAVITY;
	}
	else if (e->nx != 0)
	{
		SetState(FIRE_BALL_DISAPPEAR);
	}
}

int FireBall::IsCollidable() {
	if (state == FIRE_BALL_STATE_MARIO_SHOOT) {
		return 1;
	}
	else
		return 0;
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (isDisappear && GetTickCount64() - start_disappear > FIRE_BALL_DISAPPEAR_EFFECT_TIME_OUT) {
		start_disappear = -1;
		isDisappear = false;
		isDeleted = true;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void FireBall::Render()
{
	int ani = ID_ANI_FIRE_BALL;
	/*if (isDisappear) {
		ani = ID_ANI_FIRE_BALL_DISAPPEAR;
	}*/
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void FireBall::SetState(int state)
{
	CGameObject::SetState(state);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario_nx = mario->GetDirection();
	switch (state)
	{
	case FIRE_BALL_STATE_MARIO_SHOOT:
		vx = mario_nx * FIRE_BALL_SPEED;
		break;
	case FIRE_BALL_STATE_FPP_SHOOT_NEAR:
		vx = nx * FIRE_BALL_FPP_SHOOT_SPEED_X_NEAR;
		vy = ny * FIRE_BALL_FPP_SHOOT_SPEED_Y;
		isEnemyShoot = true;
		ay = 0;
		break;
	case FIRE_BALL_STATE_FPP_SHOOT_FAR:
		vx = nx * FIRE_BALL_FPP_SHOOT_SPEED_X_FAR;
		vy = ny * FIRE_BALL_FPP_SHOOT_SPEED_Y;
		isEnemyShoot = true;
		ay = 0;
		break;
	case FIRE_BALL_DISAPPEAR:
		vx = 0;
		vy = 0;
		ay = 0;
		start_disappear = GetTickCount64();
		isDisappear = true;
		break;
	}
}
