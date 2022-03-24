#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>

#include "Animation.h"
#include "Animations.h"
#include "AnimationSets.h"
#include "Sprites.h"
#include "Collision.h"
#include "Game.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

//#define TILE_WIDTH 16.0f
//#define TILE_HEIGHT 16.0f
//
//#define SCREEN_WIDTH 300
//#define SCREEN_HEIGHT 300


enum Type {
	MARIO = 0,
	PLATFORM = 1,
	GOOMBA = 2,
	KOOPAS = 3,
};
class CGameObject
{

protected:
	Type eType;
public:

	float x; 
	float y;

	float vx;
	float vy;

	int nx;	 

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	int state;

	bool isDeleted; 

	LPANIMATION_SET animation_set;


	DWORD dt;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; } // set vị trí object, lỗi con trỏ this ngày chỗ này
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; } // set vận tốc object
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; } // lấy vị trí object
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; } // lấy vận tốc object

	int GetState() { return this->state; } // lấy trạng thái
	virtual void Delete() { isDeleted = true;  }
	bool IsDeleted() { return isDeleted; }

	void RenderBoundingBox();
	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	CGameObject();
	CGameObject(float x, float y) :CGameObject() { this->x = x; this->y = y; }


	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) ; // update trạng thái chương trình
	virtual void Render() = 0; // render chương trình lên màn hình
	virtual void SetState(int state) { this->state = state; }



	bool CheckObjectInCamera(); // kiểm tra object có trong camera hay không
	//
	// Collision ON or OFF ? This can change depending on object's state. For example: die
	//
	virtual int IsCollidable() { return 0; };

	// When no collision has been detected (triggered by CCollision::Process)
	virtual void OnNoCollision(DWORD dt) {};

	// When collision with an object has been detected (triggered by CCollision::Process)
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};
	
	// Is this object blocking other object? If YES, collision framework will automatically push the other object
	virtual int IsBlocking() { return 1; }

	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT &o) { return o->isDeleted; }
};
