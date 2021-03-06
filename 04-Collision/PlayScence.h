#pragma once

#include <iostream>
#include <fstream>

#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "KeyEventHandler.h"
#include "Map.h"
#include "Portal.h"
#include "Utils.h"
#include "Camera.h"
#include "Platform.h"
#include "QuestionBrick.h"
#include "ColorBlock.h"
#include "Pipe.h"
#include "Coin.h"
#include "Plant.h"
#include "FirePlant.h"
#include "CoinBrick.h"
#include "HUD.h"
#include "Time.h"
#include "BackUpPlayer.h"

class CPlayScene : public CScene // màn hình giao diện của trò chơi, không phải intro scene hay là end scene
{
protected:
	CMario* player;					// A play scene has to have player, right? 
	Time* gameTime = new Time();
	int gameTimeRemain = 0;
	CGame* game = CGame::GetInstance();
	
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);


public:
	Map* map;
	CPlayScene(int id, LPCWSTR filePath);
	
	vector<LPGAMEOBJECT> objects; // con trỏ đến tất cả các đối tượng
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();


	CMario* GetPlayer() { return player; }
	Map* GetMap() { return map; }
	void PurgeDeletedObjects();
	void LoadBackup();
	void SetBackUpPlayer();


	void PutPlayerIntoScene(CMario* m)
	{
		if (dynamic_cast<CMario*>(objects[0]))
			objects[0] = m;
	}
	void SetPlayer(CMario* mario) { player = mario; }

	Time* GetGameTime() {
		return gameTime;
	}
	void SetGameTime(Time* _gameTime) {
		gameTime = _gameTime;
	}

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

class CPlayScenceKeyHandler : public CScenceKeyHandler // dùng để cài đặt logic sử lí phím 
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

typedef CPlayScene* LPPLAYSCENE;

