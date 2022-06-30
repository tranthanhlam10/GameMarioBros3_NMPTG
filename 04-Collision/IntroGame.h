#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Map.h"
#include "Time.h"
#include "WorldPlayer.h"
#include "Mario.h"
#include "Pointer.h"
#include "Ground.h"
#include "Three.h"


#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS			6
#define SCENE_SECTION_DRAWMAP			7

class IntroGame : public CScene
{
	Pointer* pointer = NULL;
	LPANIMATION background;
	LPANIMATION_SET back;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	//void _ParseSection_TILEMAP(string line);

public:
	vector<LPGAMEOBJECT> objects;
	IntroGame(int id, LPCWSTR filePath);
	Pointer* GetIntroPointer() { return pointer; }
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void Clear();
	void PurgeDeletedObjects();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef IntroGame* LPINTROSCENE;
