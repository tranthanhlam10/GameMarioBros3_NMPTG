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
#define BBOX_ALPHA 0.25f
#define TMARIO 0
#define TOBJECT 1
#define TENEMY 2
#define TCOIN 3
#define TGOLDBRICK 4
#define TCOLOR_BLOCK 5

#define ENEMY_STATE_IS_KOOPAS_ATTACKED 900 
#define ENEMY_STATE_IS_FIRE_ATTACKED 901
#define ENEMY_STATE_IS_TAIL_ATTACKED 902

enum Type {
	MARIO = TMARIO,
	OBJECT = TOBJECT,
	ENEMY = TENEMY,
	COIN = TCOIN,
	GOLDBRICK = TGOLDBRICK,
	COLORBLOCK = TCOLOR_BLOCK,

};
class CGameObject
{

protected:
	Type eType;
public:

	float x; 
	float y;

	float vx;  //vector vận tốc theo phương x
	float vy;  //vector vận tốc theo phương y

	int nx;	 // hướng
	int ny;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	int state;

	bool isDeleted; 
	int model = 0;

	LPANIMATION_SET animation_set;

	int type;
	DWORD dt;

public: 

	void SetPosition(float x, float y) { this->x = x, this->y = y; } // set vị trí object, lỗi con trỏ this ngày chỗ này
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; } // set vận tốc object
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; } // lấy vị trí object
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; } // lấy vận tốc object

	void SetType(int type) { this->type = type; }
	int GetType() { return type; }
	void SetModel(int model) { this->model = model; }
	int GetModel() { return model; }
	int GetDirection() { return this->nx; }
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	void SetDirectionX(int nx) { this->nx = nx; }
	void SetDirectionY(int ny) { this->ny = ny; }
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
	virtual int IsBlocking() { return 1; } // return 1 thi chan mario lai con return 0 la di xuyen

	~CGameObject();

	static bool IsDeleted(const LPGAMEOBJECT &o) { return o->isDeleted; }
};
