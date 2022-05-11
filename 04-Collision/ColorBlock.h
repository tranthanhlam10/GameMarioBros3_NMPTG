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

	void GetBoundingBox(float& l, float& t, float& r, float& b);

	float GetWidth() { return width; }
};

