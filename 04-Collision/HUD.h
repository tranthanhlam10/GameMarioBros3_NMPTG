#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "FontCharacter.h"


#define ID_HUD_TEX	45
#define ID_TEXT_FONT_POWER 35
// set position of font in hud
#define HUD_POS_X	155
#define HUD_POS_Y	55

#define MAP_POS_X	55
#define MAP_POS_Y	9

#define SCORE_POS_X	70
#define SCORE_POS_Y	17

#define COIN_POS_X	150
#define COIN_POS_Y	9

#define TIME_POS_X	143
#define TIME_POS_Y	17

#define LIVE_POS_X	59
#define LIVE_POS_Y	15

#define RUNNING_STACK_1_POS_X	71
#define RUNNING_STACK_2_POS_X	79
#define RUNNING_STACK_3_POS_X	87
#define RUNNING_STACK_4_POS_X	95
#define RUNNING_STACK_5_POS_X	103
#define RUNNING_STACK_6_POS_X	111
#define RUNNING_STACK_7_POS_X	119
#define RUNNING_STACK_POS_Y		7

#define LOGO_POS_X	37
#define LOGO_POS_Y	20

class HUD 
{
	float x, y;
	LPTEXTURE tex;
	LPSPRITE Sprite;
	ULONGLONG now_time;
	int time;
	FontCharacter font;
public:
	HUD(float x, float y);
	void Render(CMario* mario, int remainingTime);
	string FillNumber(string s, UINT fillNumber);
	void DrawPowerBar(float X, float Y);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}

};
