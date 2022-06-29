#pragma once
#include "GameObject.h"

#define DOOR_BBOX_WIDTH 16
#define DOOR_BBOX_HEIGHT 14

#define ID_ANI_DOOR_SCENE_1	0
#define ID_ANI_DOOR_SCENE_2 1
#define ID_ANI_DOOR_SCENE_3 2
#define ID_ANI_DOOR_SCENE_4 3
#define ID_ANI_DOOR_SCENE_5 4
#define ID_ANI_DOOR_SCENE_6 5
#define ID_ANI_DOOR_START 6
#define ID_ANI_DOOR_GIFT 7

#define SCENE_1 1
#define SCENE_2 2
#define SCENE_3 3
#define SCENE_4 4
#define SCENE_5 5
#define SCENE_6 6
#define START 0
#define SCENE_GIFT 7

class Door : public CGameObject
{
	int scene;

public:
	Door(float x, float y, int scene);
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }

	int GetScene() {
		return scene;
	}
};
