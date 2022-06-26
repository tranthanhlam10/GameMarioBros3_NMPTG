#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "Game.h"
#include "Textures.h"

#define ID_TEXT_FONT 55
#define TILE_FONT_WIDTH 8
#define TILE_FONT_A_HEIGHT				8
#define TILE_FONT_NUMBER_HEIGHT			7

class FontCharacter
{
public:
	LPTEXTURE Tex;
	void Draw(float x, float y, const string& s);
	FontCharacter();
};

