﻿#pragma once

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

class CPlayScene : public CScene // màn hình giao diện của trò chơi, không phải intro scene hay là end scene
{
protected:
	CMario* player;					// A play scene has to have player, right? 
	Map* map;
	CGame* game = CGame::GetInstance();
	
	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);


public:
	CPlayScene(int id, LPCWSTR filePath);
	
	vector<LPGAMEOBJECT> objects; // con trỏ đến tất cả các đối tượng
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();


	CMario* GetPlayer() { return player; }
	Map* GetMap() { return map; }
	void PurgeDeletedObjects();
	//friend class CPlayScenceKeyHandler;

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

