#include "Goomba.h"

CGoomba::CGoomba(float x, float y, int model):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	nx = -1;
	eType = Type::GOOMBA;
	this->model = model;
	if (model == GOOMBA_NOMAL) {
		SetState(GOOMBA_STATE_WALKING);
	}
	else {
		SetState(GOOMBA_RED_WING_STATE_WALKING);
	}
	
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x;
		top = y ;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		if (model == GOOMBA_RED_WING && state != GOOMBA_STATE_WALKING) {
			left = x  ;
			top = y - GOOMBA_RED_WING_BBOX_HEIGHT / 2;
			right = left + GOOMBA_RED_WING_BBOX_WIDTH;
			bottom = top + GOOMBA_RED_WING_BBOX_HEIGHT;
		}
		else {
			left = x ;
			top = y ;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
		}
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (e->ny != 0 )
	{
		vy = 0;
		isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		nx = -nx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if (model == GOOMBA_RED_WING && state != GOOMBA_STATE_DIE && state != GOOMBA_STATE_WALKING) 
	{
		if (state == GOOMBA_RED_WING_STATE_WALKING && GetTickCount64() - wing_walk_start > LIMIT_TIME_WING_WALKING && isWalking) 
		{ 
			jumpStack = 0;
			wing_walk_start = -1;
			isWalking = false;
			SetState(GOOMBA_RED_WING_STATE_JUMP_LOW);
		}
		else if (!isWalking) {

			if (jumpStack == LIMIT_JUMP_STACK) 
			{ 
				SetState(GOOMBA_RED_WING_STATE_JUMP_HIGH);
				jumpStack = -1;
			}
			else 
			{
				if (jumpStack == -1 && isOnPlatform) 
				{
					SetState(GOOMBA_RED_WING_STATE_WALKING);
				}
				else
					if (isOnPlatform && isJumping) 
					{
						jumpStack++;
						isJumping = false;
						SetState(GOOMBA_RED_WING_STATE_JUMP_LOW);
					}
			}
		}
	}


	if (vy <= -LIMIT_HIGH_LOW && state == GOOMBA_RED_WING_STATE_JUMP_LOW)
	{
		vy = -LIMIT_HIGH_LOW;
		ay = GOOMBA_GRAVITY;
	}
	if (vy <= -LIMIT_HIGH_JUMP && state == GOOMBA_RED_WING_STATE_JUMP_HIGH)
	{
		vy = -LIMIT_HIGH_JUMP;
		ay = GOOMBA_GRAVITY;

	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}


void CGoomba::Render()
{

	int ani = GOOMBA_ANI_WALKING;
	if (model == GOOMBA_NOMAL) 
	{
		if (state == GOOMBA_STATE_DIE)
		{
			ani = GOOMBA_ANI_DIE;
		}
	}
	if (model == GOOMBA_RED_WING) 
	{
		if (state == GOOMBA_STATE_WALKING) 
		{
			ani = GOOMBA_ANI_RED_WALK;
		}
		else if (state == GOOMBA_STATE_DIE) 
		{
			ani = GOOMBA_ANI_RED_DIE;
		}
		else if (state == GOOMBA_RED_WING_STATE_WALKING) 
		{
			ani = GOOMBA_ANI_RED_WING_WALK;
		}
		else if (state == GOOMBA_RED_WING_STATE_JUMP_HIGH || state == GOOMBA_RED_WING_STATE_JUMP_LOW) 
		{
			ani = GOOMBA_ANI_RED_WING_JUMP;
		}
	}

	
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_RED_WING_STATE_WALKING:
		vx = nx * GOOMBA_WALKING_SPEED;
		wing_walk_start = GetTickCount64();
		isWalking = true;
		break;
	case GOOMBA_RED_WING_STATE_JUMP_LOW:
		vy = -JUMP_LOW_SPEED;
		isOnPlatform = false;
		isJumping = true;
		break;
	case GOOMBA_RED_WING_STATE_JUMP_HIGH:
		vy = -JUMP_HIGH_SPEED;
		isOnPlatform = false;
		isJumping = true;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}
