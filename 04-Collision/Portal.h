#pragma once
#include "GameObject.h"

/*
	Object that triggers scene switching
*/


class CPortal : public CGameObject // render bbox
{
	float scene_id;	// target scene to switch to 

	float width;
	float height;
public:
	CPortal(float l, float t, float r, float b, float scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	float GetSceneId() { return scene_id; }
};
