#pragma once

#include"Mario.h"
#include "Time.h"
class BackUpPlayer
{
public:
	static BackUpPlayer* __instance;
	int health = 1;
	int money = 0;
	DWORD time = 0;
	int score = 0;
	int level = MARIO_LEVEL_SMALL;
	int scene = 0;
	int coin = 0;
	Time* gameTime = new Time();

	static BackUpPlayer* GetInstance();
	void BackUpMario(CMario* mario);
	void LoadBackUp(CMario* mario);
};
