#include "Time.h"
Time::Time()
{
	this->temp = 0;
	this->time = 0;
}

void Time::Update(DWORD dt)
{
	if (temp + dt <= SECOND) {
		temp += dt;
	}
	else {
		temp = 0;
		time++;
	}
}

void Time::SetTime(int t)
{
	time = t;
}

int Time::GetTime()
{
	return time;
}