#pragma once


#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Map.h"
#include "Time.h"
#include "WorldPlayer.h"
#include "Mario.h"

#define ADJUST_PADDING 10


#define SCENE_SECTION_UNKNOWN			-1
#define SCENE_SECTION_TEXTURES			2
#define SCENE_SECTION_SPRITES			3
#define SCENE_SECTION_ANIMATIONS		4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS			6
#define SCENE_SECTION_DRAWMAP			7


#define GAME_TIME_LIMIT 300
#define HUD_HEIGHT 32

class WorldScene : public CScene
{
	WorldPlayer* player = NULL;
	CMario* mario = NULL;
	Time* gameTime = new Time();
	CGame* game = CGame::GetInstance();
	int gameTimeRemain = 0;
	bool isTurnOnCamY = false;

	
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);

public:

	Map* map ;
	WorldScene(int id, LPCWSTR filePath);
	WorldPlayer* GetPlayer() { return player; }
	Map* GetMap() { return map; }
	vector<LPGAMEOBJECT> objects;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void Clear();
	void PurgeDeletedObjects();
	void LoadBackup();
	void SetBackUpPlayer();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef WorldScene* LPWORLDSCENE;
