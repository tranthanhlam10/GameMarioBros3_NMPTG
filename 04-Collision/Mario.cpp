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



void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) //cần phải viết lại hàm update
{
	CGame* game = CGame::GetInstance();
	CGameObject::Update(dt);
	
	float mw = ((CPlayScene*)game->GetCurrentScene())->GetMap()->GetMapWidth();
	float mh = ((CPlayScene*)game->GetCurrentScene())->GetMap()->GetMapHeight(); 
  

     vy += ay * dt; // đây là công thức tính trọng lực tác động lên mario
	 vx += ax * dt + nx * ax;



	 

	 if (abs(vx) > MARIO_WALKING_SPEED) {

		 vx = nx * MARIO_WALKING_SPEED;
	 }


	 // gioi han di chuyen theo phuong y
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
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
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
	if (e->ny != 0 && e->obj->IsBlocking()) // điều kiện để xảy ra va chạm
	{
		vy = 0;
		if (e->ny < 0) { 
			isOnPlatform = true; // va chạm với platform
			vy = 0;
			isJumping = false; // lí do sai khong phai cho nay
		}
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e) // sử lí va chạm khi cham nấm
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
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
					level = MARIO_LEVEL_SMALL;
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

void CMario::Render()
{CAnimations* animations = CAnimations::GetInstance();

	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			//mario jump
			if (vy <0 ) {
				if (nx > 0)
					ani = MARIO_ANI_BIG_JUMP_RIGHT;
				else
					ani = MARIO_ANI_BIG_JUMP_LEFT;
			}
			else
			{
				if (vx == 0) 
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
					else
					ani = MARIO_ANI_BIG_WALKING_RIGHT;
				}

				else 
				{
					if (nx > 0)
						ani = MARIO_ANI_BIG_TURN_LEFT_BACK_RIGHT;
					else
					ani = MARIO_ANI_BIG_WALKING_LEFT;
				
				}
			}

		} 
	  
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (vy < 0) {
				if (nx > 0)
					ani = MARIO_ANI_SMALL_JUMP_RIGHT;
				else
					ani = MARIO_ANI_SMALL_JUMP_LEFT;

			} else
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
					else
						ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				}

				else
				{
					if (nx > 0)
						ani = MARIO_ANI_SMALL_TURN_LEFT_BACK_RIGHT;
					else
						ani = MARIO_ANI_SMALL_WALKING_LEFT;

				}
			}
	
		} 

		else if (level == MARIO_LEVEL_RACOON)
		{
			if (vy < 0) {
				if (nx > 0)
					ani = MARIO_ANI_RACOON_JUMP_RIGHT;
				else
					ani = MARIO_ANI_RACOON_JUMP_LEFT;

			}
			else
			{
				if (vx == 0)
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
					else
						ani = MARIO_ANI_RACOON_WALKING_RIGHT;
				}

				else
				{
					if (nx > 0)
						ani = MARIO_ANI_RACOON_TURN_LEFT_BACK_RIGHT;
					else
						ani = MARIO_ANI_RACOON_WALKING_LEFT;

				}
			}


		}
		else if (level == MARIO_LEVEL_FIRE)
		{
			if (vy < 0) {
				if (nx > 0)
					ani = MARIO_ANI_FIRE_JUMP_RIGHT;
				else
					ani = MARIO_ANI_FIRE_JUMP_LEFT;

			}
			else
			
			{
				if (vx == 0)
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
					else
						ani = MARIO_ANI_FIRE_WALKING_RIGHT;
				}

				else
				{
					if (nx > 0)
						ani = MARIO_ANI_FIRE_TURN_LEFT_BACK_RIGHT;
					else
						ani = MARIO_ANI_FIRE_WALKING_LEFT;

				}
			}


		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y);

   RenderBoundingBox();
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
	case MARIO_STATE_JUMP: // State nay khong van de
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
	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom) // bbox là cái nền màu đỏ trong object
{

	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_RACOON)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
	    bottom = y + MARIO_BIG_BBOX_HEIGHT;
	
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
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

	DebugOut(L"[INFO] Mario Level: %d\n", this->level);
	DebugOut(L"[INFO] Mario Level: %d\n", this->state);

}
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

