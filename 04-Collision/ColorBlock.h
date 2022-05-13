#pragma once
#include "GameObject.h"
class CColorBlock : public CGameObject
{
public:

	float width;
	float height;

	CColorBlock(float x, float y, float length, float height);
	void Render() {};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	float GetWidth() { return width; }
};

