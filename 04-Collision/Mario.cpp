#include <algorithm>
#include "debug.h"
#include <assert.h>
#include "Mario.h"
#include "Game.h"
#include "Utils.h"
#include "Portal.h"
#include "Goomba.h"
#include "Coin.h"
#include "GameObject.h"
#include "Collision.h"
#include "PlayScence.h"
#include "ColorBlock.h"
#include "Flower.h"
#include "FireBall.h"
#include "Goomba.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGame* game = CGame::GetInstance();
	CGameObject::Update(dt);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	
	float mw = ((CPlayScene*)game->GetCurrentScene())->GetMap()->GetMapWidth();
	float mh = ((CPlayScene*)game->GetCurrentScene())->GetMap()->GetMapHeight(); 
  

     vy += ay * dt; 
	 vx += ax * dt + nx * runningStack * ax;

	
	 // giới hạn chuyển động theo phuong x
	 if (abs(vx) > MARIO_WALKING_SPEED) 
	 {
		 if (!isRunning) {
			 vx = nx * MARIO_WALKING_SPEED;
		 }
		 else if (abs(vx) >= MARIO_RUNNING_SPEED){
			 if (runningStack < MARIO_POWER_FULL) {
				 vx = nx * MARIO_RUNNING_SPEED;
			 }
			 else
			 {
				 vx = nx * MARIO_RUNNING_MAX_SPEED;
			 }
		 }
	 }

	 if (vx < 0 && nx > 0 && !isWalking)
	 {
		 vx = 0;
		 ax = 0;
	 }
	 if (vx > 0 && nx < 0 && !isWalking)
	 {
		 vx = 0;
		 ax = 0;
	 }

	 // gioi han di chuyen theo phuong y
	 if (y <= 0) {
		 y = 0;
	 }
	 if (vy <= -MARIO_JUMP_SPEED_MAX && !isRunningMax) {
		 vy = -MARIO_JUMP_SPEED_MAX;
		 ay = MARIO_GRAVITY;
	 }

	 if (vy <= -MARIO_JUMP_RUN_SPEED_Y && isRunningMax) {
		 vy = -MARIO_JUMP_RUN_SPEED_Y;
		 ay = MARIO_GRAVITY;
	 }
	 if (vy < 0) {
		 isOnPlatform = false;
	 }

	 if (level == MARIO_LEVEL_RACOON && vy > 0) {
		 pendingFallSlow = true;
	 }

	 if (GetTickCount64() - flying_start > LIMIT_MARIO_RACCOON_FLY_TIME && isFlying)
	 {
		 isFlying = false;
		 isFlapping = false;
		 pendingFallSlow = true;
	 }

	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount64() - running_start > POWER_STACK_TIME && isRunning )
	{
		running_start = GetTickCount64();
		runningStack++;
		if (runningStack > MARIO_POWER_FULL)
		{
			runningStack = MARIO_POWER_FULL;
			isRunningMax = true;
		}
	}

	if (GetTickCount64() - running_stop > POWER_STACK_LOST_TIME && runningStack && (!isRunning || vx == 0))
	{
		running_stop = GetTickCount64();
		isRunningMax = false;
		runningStack--;
		if (runningStack <= 0)
		{
			(runningStack = 0);

		}
		DebugOut(L"[INFO] powerStack! %d \n", runningStack);
	}
	if (isMoveOverBlockColor) {
		y -= ADJUST_MARIO_COLLISION_WITH_COLOR_BLOCK;
		vy = -MARIO_JUMP_SPEED_MAX;
		isMoveOverBlockColor = false;
	}

	if (GetTickCount64() - shoot_start > MARIO_FIRE_TIME_SHOOT && isPendingShootFireBall) {
		shoot_start = -1;
		isPendingShootFireBall = false;
	}

	if (isShootingFireBall && level == MARIO_LEVEL_FIRE)
	{
		if (TotalFire.size() < MARIO_FIRE_BALL_LIMIT)
		{
			MarioShootFireBall();
			isPendingShootFireBall = true;
			isShootingFireBall = false;
		}
	}

	for (size_t i = 0; i < TotalFire.size(); i++)
	{
		TotalFire[i]->Update(dt, coObjects);
		if (TotalFire[i]->isDeleted) {
			TotalFire.erase(TotalFire.begin() + i);
		}
	}

	
	if (x <= MARIO_BIG_BBOX_WIDTH) {
		x = MARIO_BIG_BBOX_WIDTH;
	}
	if (x + MARIO_BIG_BBOX_WIDTH >= scene->map->GetMapWidth()) {
		x = (float)(scene->map->GetMapWidth() - MARIO_BIG_BBOX_WIDTH);
	}
	if (y <= 0) {
		y = 0;
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt) // Không có va chạm
{
	
    x += vx * dt; 
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e) // xác định xem va chạm với ai
{
	if (e->ny < 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) { 
			isOnPlatform = true; // va chạm với platform
			vy = 0;
			isJumping = false; 
			pendingFallSlow = false;
			isFlying = false;
		}
	}
	if (e->ny > 0) {
		vy = 0;
		ay = MARIO_GRAVITY;
	}
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CColorBlock*>(e->obj))
		OnCollisionWithColorBlock(e);
	else if (dynamic_cast<Flower*>(e->obj))
		OnCollisionWithFlower(e);

}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e) // sử lí va chạm khi cham nấm
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			if (goomba->GetModel() == GOOMBA_NOMAL) {
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else
				if (goomba->GetState() == GOOMBA_STATE_WALKING) {
					goomba->SetState(GOOMBA_STATE_DIE);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
		
				}
				else {
					goomba->SetState(GOOMBA_STATE_WALKING);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level--;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e) // sử lí khi va chạm với tiền
{
	e->obj->Delete();
	coin++;
}
void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e) {
	CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
	if (e->ny > 0 && !questionBrick->isEmpty) {
		questionBrick->SetState(QUESTION_BRICK_STATE_UP);
	}
}
void CMario::OnCollisionWithColorBlock(LPCOLLISIONEVENT e) // sử lí khi va chạm với tiền
{
	if (e->ny > 0) {
		isMoveOverBlockColor = true;
	}
}

void CMario::OnCollisionWithFlower(LPCOLLISIONEVENT e)
{
	level = MARIO_LEVEL_FIRE;
	//obj = new CEffectScore(x, y, SCORE_EFFECT_1000);
	//ListEffect.push_back(obj);
	e->obj->Delete();
}


void CMario::Render()
{CAnimations* animations = CAnimations::GetInstance();

	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			if (!isOnPlatform)
			{
				if (isRunningMax) 
				{
					if (nx >= 0)
						ani = MARIO_ANI_BIG_JUMP_RUN_RIGHT;
					else
						ani = MARIO_ANI_BIG_JUMP_RUN_LEFT;
				}
				else
				{


					//mario jump
					if (vy < 0) {
						if (nx > 0)
							ani = MARIO_ANI_BIG_JUMP_RIGHT;
						else
							ani = MARIO_ANI_BIG_JUMP_LEFT;
					}

					else {
						if (nx >= 0)
							ani = MARIO_ANI_BIG_FALL_RIGHT;
						else
							ani = MARIO_ANI_BIG_FALL_LEFT;
					}
				}
			}
			else 
			{
				if (isSitting)
				{
					if (nx > 0)
						ani = MARIO_ANI_BIG_SIT_RIGHT;
					else
						ani = MARIO_ANI_BIG_SIT_LEFT;
				}
				else if (vx == 0) 
					{
						//mario dung yen
						if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
						else ani = MARIO_ANI_BIG_IDLE_LEFT;
					}
				else if (vx > 0)
				{
					if (nx < 0)
						//mario di bo
						ani = MARIO_ANI_BIG_TURN_RIGHT_BACK_LEFT;
					else if (isRunningMax)
						ani = MARIO_ANI_BIG_RUN_MAX_RIGHT;
					else if (isRunning)
						ani = MARIO_ANI_BIG_RUN_RIGHT;
					else
					    ani = MARIO_ANI_BIG_WALKING_RIGHT;
				}

				else 
				{
					if (nx > 0)
						ani = MARIO_ANI_BIG_TURN_LEFT_BACK_RIGHT;
					else if (isRunningMax)
						ani = MARIO_ANI_BIG_RUN_MAX_LEFT;
					else if (isRunning)
						ani = MARIO_ANI_BIG_RUN_LEFT;
					else
					    ani = MARIO_ANI_BIG_WALKING_LEFT;
				
				}
			}

		} 
	  
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (!isOnPlatform)
			{
				if (isRunningMax)
				{
					if (nx >= 0)
						ani = MARIO_ANI_SMALL_JUMP_RUN_RIGHT;
					else
						ani = MARIO_ANI_SMALL_JUMP_RUN_LEFT;
				}
				else
				{
					if (vy < 0) {
						if (nx > 0)
							ani = MARIO_ANI_SMALL_JUMP_RIGHT;
						else
							ani = MARIO_ANI_SMALL_JUMP_LEFT;

					}
					else {
						if (nx >= 0)
							ani = MARIO_ANI_SMALL_FALL_RIGHT;
						else
							ani = MARIO_ANI_SMALL_FALL_LEFT;
					}
				}
			}
			else
			{
				if (vx == 0)
				{
					//mario dung yen
					if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
					else ani = MARIO_ANI_SMALL_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (nx < 0)
						//mario di bo
						ani = MARIO_ANI_SMALL_TURN_RIGHT_BACK_LEFT;
					else if (isRunningMax)
						ani = MARIO_ANI_SMALL_RUN_MAX_RIGHT;
					else if (isRunning)
						ani = MARIO_ANI_SMALL_RUN_RIGHT;
					else
						ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				}
				else
				{
					if (nx > 0)
						ani = MARIO_ANI_SMALL_TURN_LEFT_BACK_RIGHT;
					else if (isRunningMax)
						ani = MARIO_ANI_SMALL_RUN_MAX_LEFT;
					else if (isRunning)
						ani = MARIO_ANI_SMALL_RUN_LEFT;
					else
						ani = MARIO_ANI_SMALL_WALKING_LEFT;

				}
			}
	
		} 

		else if (level == MARIO_LEVEL_RACOON)
		{
			if (!isOnPlatform) // không có trên mặt đất
			{
					if (isFlying && isFlapping) {
						if (nx >= 0)
							ani = MARIO_ANI_RACOON_FLY_RIGHT;
						else
							ani = MARIO_ANI_RACOON_FLY_LEFT;
					}
					else if (isRunningMax)
					{
						if (nx >= 0)
							ani = MARIO_ANI_RACOON_JUMP_RUN_RIGHT;
						else
							ani = MARIO_ANI_RACOON_JUMP_RUN_LEFT;
					}
					else
					{
						if (vy < 0) {
							if (nx > 0)
								ani = MARIO_ANI_RACOON_JUMP_RIGHT;
							else
								ani = MARIO_ANI_RACOON_JUMP_LEFT;

						}
					
						else 
						{
							if (!isFlying)
							{
								if (nx >= 0)
									ani = MARIO_ANI_RACOON_FALL_RIGHT;
								else
									ani = MARIO_ANI_RACOON_FALL_LEFT;
							}
							else 
							{
								if (nx >= 0)
									ani = MARIO_ANI_RACOON_FALL_FLY_RIGHT;
								else
									ani = MARIO_ANI_RACOON_FALL_FLY_LEFT;
							}

							if (isFallSlow) 
							{
								if (nx >= 0)
									ani = MARIO_ANI_RACOON_FALL_SLOW_RIGHT;
								else
									ani = MARIO_ANI_RACOON_FALL_SLOW_LEFT;
							}
					
						}
					}
			}
			else // trên mặt đất
			{
				if (isSitting)
				{
					if (nx > 0)
						ani = MARIO_ANI_RACOON_SIT_RIGHT;
					else
						ani = MARIO_ANI_RACOON_SIT_LEFT;
				}
				else if (vx == 0)
				{
					//mario dung yen
					if (nx > 0) ani = MARIO_ANI_RACOON_IDLE_RIGHT;
					else ani = MARIO_ANI_RACOON_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (nx < 0)
						//mario di bo
						ani = MARIO_ANI_RACOON_TURN_RIGHT_BACK_LEFT;
					else if (isRunningMax)
						ani = MARIO_ANI_RACOON_RUN_MAX_RIGHT;
					else if (isRunning)
						ani = MARIO_ANI_RACOON_RUN_RIGHT;
					else
						ani = MARIO_ANI_RACOON_WALKING_RIGHT;
				}

				else
				{
					if (nx > 0)
						ani = MARIO_ANI_RACOON_TURN_LEFT_BACK_RIGHT;
					else if (isRunningMax)
						ani = MARIO_ANI_RACOON_RUN_MAX_LEFT;
					else if (isRunning)
						ani = MARIO_ANI_RACOON_RUN_LEFT;
					else
						ani = MARIO_ANI_RACOON_WALKING_LEFT;

				}
			}


		}
		else if (level == MARIO_LEVEL_FIRE)
		{
			if (!isOnPlatform)
			{
				if (isRunningMax)
				{
					if (nx >= 0)
						ani = MARIO_ANI_FIRE_JUMP_RUN_RIGHT;
					else
						ani = MARIO_ANI_FIRE_JUMP_RUN_LEFT;
				}
				else
				{
					if (vy < 0) {
						if (nx > 0)
							ani = MARIO_ANI_FIRE_JUMP_RIGHT;
						else
							ani = MARIO_ANI_FIRE_JUMP_LEFT;

					}
					else {
						if (nx >= 0)
							ani = MARIO_ANI_FIRE_FALL_RIGHT;
						else
							ani = MARIO_ANI_FIRE_FALL_LEFT;
					}
				}
			}
			else
			{
				if (isSitting)
				{
					if (nx > 0)
						ani = MARIO_ANI_FIRE_SIT_RIGHT;
					else
						ani = MARIO_ANI_FIRE_SIT_LEFT;
				}
				else if (isPendingShootFireBall) 
				{
					if (nx > 0) 
					{
						ani = MARIO_ANI_FIRE_SHOOT_RIGHT;
					}
					else
						ani = MARIO_ANI_FIRE_SHOOT_LEFT;
				}
				else if (vx == 0)
				{
					//mario dung yen
					if (nx > 0) ani = MARIO_ANI_FIRE_IDLE_RIGHT;
					else ani = MARIO_ANI_FIRE_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (nx < 0)
						//mario di bo
						ani = MARIO_ANI_FIRE_TURN_RIGHT_BACK_LEFT;
					else if (isRunningMax)
						ani = MARIO_ANI_FIRE_RUN_MAX_RIGHT;
					else if (isRunning)
						ani = MARIO_ANI_FIRE_RUN_RIGHT;
					else
						ani = MARIO_ANI_FIRE_WALKING_RIGHT;
				}

				else
				{
					if (nx > 0)
						ani = MARIO_ANI_FIRE_TURN_LEFT_BACK_RIGHT;
					else if (isRunningMax)
						ani = MARIO_ANI_FIRE_RUN_MAX_LEFT;
					else if (isRunning)
						ani = MARIO_ANI_FIRE_RUN_LEFT;
					else
						ani = MARIO_ANI_FIRE_WALKING_LEFT;
				}
			}


		}

		for (int i = 0; i < TotalFire.size(); i++)
		{
			TotalFire[i]->Render();
		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y);

 // RenderBoundingBox();
}



void CMario::Decelerate()
{
	if (vx > 0)
	{
		ax = -MARIO_DECELERATE_SPEED;
	}
	if (vx < 0)
	{
		ax = MARIO_DECELERATE_SPEED;
	}
}

void CMario::MarioShootFireBall()
{
	FireBall* fireBall = new FireBall(x + ADJUST_MARIO_SHOOT_FIRE_X, y + ADJUST_MARIO_SHOOT_FIRE_Y);
	fireBall->SetState(FIRE_BALL_STATE_MARIO_SHOOT);
	TotalFire.push_back(fireBall);
}



void CMario::SetState(int state) // set trạng thái cho mario
{
	CGameObject::SetState(state);

	switch (state)
	{

	case MARIO_STATE_WALKING_RIGHT:
		ax = MARIO_ACCEL_WALK_X;
		isWalking = true;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		ax = -MARIO_ACCEL_WALK_X;
		isWalking = true;
		nx = -1;
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		running_start = GetTickCount64();
		nx = 1;
		isRunning = true;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		running_start = GetTickCount64();
		nx = -1;
		isRunning = true;
		break;
	case MARIO_STATE_JUMP:
	    isJumping = true;
		if (isOnPlatform) {

			if (vy > -MARIO_JUMP_SPEED_MIN)
			{
				vy = -MARIO_JUMP_SPEED_MIN;
				
			}
			if (isRunningMax)
			{
				vy = -MARIO_JUMP_RUN_SPEED_Y;

				if (level == MARIO_LEVEL_RACOON) {
					isFlying = true;
					flying_start = GetTickCount64(); 
				}
			}
		    ay = -MARIO_ACCEL_JUMP_Y;
		}
		break;
	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			Decelerate();
			vy = 0.0f;
		}
		break;
	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;
	case MARIO_STATE_RELEASE_RUN:
		isRunning = false;
		running_stop = GetTickCount64();
		break;
	case MARIO_STATE_IDLE:
		Decelerate();
		isWalking = false;
		ay = MARIO_GRAVITY;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_SHOOTING:
		isShootingFireBall = true;
		shoot_start = GetTickCount64();
		break;
	case MARIO_RACOON_STATE_FLAPPING:
		ay = -MARIO_RACCOON_FLAPPING_SPEED;
		isFlapping = true;
		break;
	case MARIO_RACOON_STATE_FALL_SLOW:
		isFallSlow = true;
		vy = -MARIO_RACCOON_FALL_SLOW_SPEED;
		break;

	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom) // bbox là cái nền màu đỏ trong object
{

	if (level != MARIO_LEVEL_SMALL)
	{
		if (isSitting)
		{
			left = x ;
			top = y ;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x;
			top = y ;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT ;

		}
	}
	else
	{
		left = x;
		top = y	;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int level) // set cấp độ cho mario
{
	// Adjust position to avoid falling off platfor
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;

	}
	this->level = level ;	

}
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

