#include <d3dx9.h>
#include <algorithm>
#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Utils.h"


#define TILE_WIDTH 16.0f
#define TILE_HEIGHT 16.0f

#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 300

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	state = -1;
	isDeleted = false;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}


void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy; 
	CGame::GetInstance()->GetCamPos(cx, cy);

	CGame::GetInstance()->Draw(x - cx, y - cy, bbox, rect.left, rect.top, rect.right, rect.bottom, 0.25f);
	
}

CGameObject::~CGameObject()
{

}
bool CGameObject::CheckObjectInCamera()
{
	float w = TILE_WIDTH;
	float h = TILE_HEIGHT;
	if (this->x + w < (CGame::GetInstance()->GetCamX()) || (CGame::GetInstance()->GetCamX()) + SCREEN_WIDTH + 100 < this->x)
		return false;
	if (this->y + h < (CGame::GetInstance()->GetCamY() - 32.0f) || (CGame::GetInstance()->GetCamY()) + SCREEN_HEIGHT + 32.0f < this->y)
		return false;
	return true;
}