#include "FontCharacter.h"

FontCharacter::FontCharacter()
{
	Tex = CTextures::GetInstance()->Get(55);
}

void FontCharacter::Draw(float x, float y, const string& s) {

	for (UINT i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;

		if (s[i] == '!') {
			int left = NUM_OF_LETTER * TILE_FONT_WIDTH;
			int right = left + NOTE_OF_EXCLAMATION_WIDTH;
			int top = TOP_LETTER;
			int bottom = top + TILE_FONT_LETTER_HEIGHT;
			LPSPRITE spriteTile = new CSprite(99, 208, 0, 212, 8, Tex);
			spriteTile->Draw(x + i * TILE_FONT_WIDTH, y);
		}

		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			int id = s[i] - 'A';
			int left = id % 26 * TILE_FONT_WIDTH;
			int top = TOP_LETTER;
			int right = left + TILE_FONT_WIDTH;
			int bottom = top + TILE_FONT_A_HEIGHT;
			LPSPRITE SpriteTile = new CSprite(id, left, top, right, bottom, Tex);
			SpriteTile->Draw(x + i * TILE_FONT_WIDTH, y);
		}

		else if (s[i] >= '0' && s[i] <= '9')
		{
			int id =  s[i] - '0';
			int left = id % 26 * TILE_FONT_WIDTH;
			int top = TILE_FONT_A_HEIGHT;
			int right = left + TILE_FONT_WIDTH;
			int bottom = top + TILE_FONT_NUMBER_HEIGHT;
			LPSPRITE SpriteTile = new CSprite(id, left, top, right, bottom, Tex);
			SpriteTile->Draw(x + i * TILE_FONT_WIDTH, y);
		}
	}
	
}



