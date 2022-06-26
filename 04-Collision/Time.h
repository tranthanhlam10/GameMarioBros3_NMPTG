#pragma once

#pragma once
#include "GameObject.h"
#define SECOND 1000
class Time
{
	DWORD temp;
	int time;
public:
	Time();
	void Update(DWORD dt);
	void SetTime(int t);
	int GetTime();
};

