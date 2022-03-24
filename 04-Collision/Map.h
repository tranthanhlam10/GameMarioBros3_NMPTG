#pragma once
#include "Game.h"
#include "Sprites.h"
#include "Sprite.h"
#include <fstream>
#include "Utils.h"
#include <string>
#include <string.h>
#include "Textures.h"
#include "debug.h"


#define TILE_WIDTH 16.0f
#define TILE_HEIGHT 16.0f
#define COLOR_BLOCK_GET_THROUGH 100

class Map {

	static Map* __instance;
	LPTEXTURE Tex;
	int ColumnMap, RowMap;
	int ColumnTile, RowTile;
	int TotalTile;
	float** TileMap;
	vector<LPSPRITE> Tiles;
	float CamX, CamY;

public:
	Map(int TexID,
		int RowMap,
		int ColumnMap,
		int RowTile,
		int ColumnTile,
		int TotalTile);
	~Map();
	void SetMap(float** tilemap);
	void GetSpriteTile();
	void DrawMap();
	void SetCamPos(float x, float y) {
		CamX = x;
		CamY = y;
	}
	float GetMapWidth(); // còn vuong 2 thằng này nữa thì xong load map
	float GetMapHeight();
	int GetColumnMap() { return ColumnMap; }
};

