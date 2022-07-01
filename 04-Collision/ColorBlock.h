#pragma once
#include "GameObject.h"
class CColorBlock : public CGameObject
{
public:

	float width;
	float height;
	/*int is_blocking = 1;*/

	CColorBlock(float x, float y, float length, float height);
	void Render() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	//int IsBlocking()/* { return this->is_blocking; }*/;
	//void SetIsBlocking(int value) {
	//	this->is_blocking = value;
	//}
	
	float GetWidth() { return width; }
};

