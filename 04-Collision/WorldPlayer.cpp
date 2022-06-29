#include "WorldPlayer.h"
#include "BackUpPlayer.h"
#include "Door.h"
#include "Block.h"


WorldPlayer::WorldPlayer(float x, float y) : CGameObject()
{
	SetState(MARIO_WORLD_MAP_STATE_IDLE);
	this->x = x;
	this->y = y;
	this->ay = 0;
	this->ax = 0;
	this->level = BackUpPlayer::GetInstance()->level;
}

void WorldPlayer::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void WorldPlayer::OnCollisionWith(LPCOLLISIONEVENT e)
{
	/*if (dynamic_cast<CBlockObj*>(e->obj))
		OnCollisionWithBlockObj(e);
	if (dynamic_cast<CDoor*>(e->obj))
		OnCollisionWithDoor(e);*/
}

void WorldPlayer::OnCollisionWithDoor(LPCOLLISIONEVENT e)
{
	//CDoor* door = dynamic_cast<CDoor*>(e->obj);
	//sceneSwitch = door->GetScene();
}

void WorldPlayer::OnCollisionWithBlockObj(LPCOLLISIONEVENT e)
{
	Block* block = dynamic_cast<Block*>(e->obj);
	vx = 0;
	vy = 0;
	allowLeft = block->allowLeft;
	allowRight = block->allowRight;
	allowBottom = block->allowBottom;
	allowTop = block->allowTop;
	if (e->nx != 0) {
		x = x - e->nx * MARIO_WORLD_MAP_BBOX_WIDTH;
	}
	if (e->ny != 0) {
		y = y - e->ny * MARIO_WORLD_MAP_BBOX_WIDTH;
	}
}


void WorldPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void WorldPlayer::Render() {

}


void WorldPlayer::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARIO_WORLD_MAP_STATE_IDLE:
	{
		vx = vy = 0;
		break;
	}
	case MARIO_WORLD_MAP_STATE_WALK_RIGHT:
	{
		vx = MARIO_WORLD_MAP_SPEED;
		vy = 0;
		break;
	}
	case MARIO_WORLD_MAP_STATE_WALK_LEFT:
	{
		vx = -MARIO_WORLD_MAP_SPEED;
		vy = 0;
		break;
	}
	case MARIO_WORLD_MAP_STATE_WALK_TOP:
	{
		vx = 0;
		vy = -MARIO_WORLD_MAP_SPEED;
		break;
	}
	case MARIO_WORLD_MAP_STATE_WALK_BOTTOM:
	{
		vx = 0;
		vy = MARIO_WORLD_MAP_SPEED;
		break;
	}
	}
}