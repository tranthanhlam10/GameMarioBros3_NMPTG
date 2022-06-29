#include "Map.h"
#include <fstream>
#include <iostream>


Map::Map(int TexID, int RowMap, int ColumnMap, int RowTile, int ColumnTile, int TotalTile)
{
	Tex = CTextures::GetInstance()->Get(TexID);
	this->RowMap = RowMap; // thông số hàng
	this->ColumnMap = ColumnMap; // thông số cột
	this->RowTile = RowTile; // 16px
	this->ColumnTile = ColumnTile; //16px
	this->TotalTile = TotalTile; // số tile map tổng công của map
	CamX = CamY = 0;
}


Map::~Map()
{
}

void Map::SetMap(float** tilemap) {
	TileMap = tilemap;
}

// ve map
void Map::DrawMap() {
	float FirstColumn = floor(CamX / TILE_WIDTH);
	float LastColumn = ceil((CamX + CGame::GetInstance()->GetScreenWidth()) / TILE_WIDTH);

	if (LastColumn >= ColumnMap)
		LastColumn = (float)(ColumnMap - 1.f);

	for (int CurrentRow = 0; CurrentRow < RowMap; CurrentRow++) {
		for (int CurrentColumn = 0; CurrentColumn <= LastColumn; CurrentColumn++) {	//2 vong lap ve map
			int index = int(TileMap[CurrentRow][CurrentColumn] - 1);
			if (index < TotalTile) {	//dem tong so luong tile da ve
				Tiles.at(index)->Draw(float(CurrentColumn * TILE_WIDTH), float(CurrentRow * TILE_HEIGHT));
			}
		}
	}
}

void Map::GetSpriteTile() {

	for (int id = 0; id < TotalTile; id++) {
		float left = (id % ColumnTile * TILE_WIDTH);
		float top = (id / ColumnTile * TILE_HEIGHT);
		float right = left + TILE_WIDTH;
		float bottom = top + TILE_HEIGHT;

		LPSPRITE SpriteTile = new CSprite(id, (int)left, (int)top, (int)right, (int)bottom, Tex);
		this->Tiles.push_back(SpriteTile);
	}

}
float Map::GetMapHeight() {
	return RowMap * TILE_HEIGHT;
}
float Map::GetMapWidth() {
	return ColumnMap * TILE_WIDTH - 1;
}
