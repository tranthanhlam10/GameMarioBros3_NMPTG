#include "HUD.h"
#include "FontCharacter.h"
#include <string>

HUD::HUD(float x, float y)
{

	this->x = x;
	this->y = y;
	now_time = GetTickCount64();
	tex = CTextures::GetInstance()->Get(ID_HUD_TEX);
	Sprite = new CSprite(0, 0, 0, 320, 120, tex);


}

string HUD::FillNumber(string s, UINT fillNumber)
{
	while (s.size() > fillNumber)
		s = s.substr(0, fillNumber);
	while (s.size() < fillNumber)
		s = "0" + s;
	return s;
}

void HUD::Render(CMario* mario, int remainingTime)
{
	CGame* game = CGame::GetInstance();
	if (game->GetScene() == MAP1_1_1) {
		Sprite->Draw(x + HUD_POS_X, y + HUD_POS_Y- ADJUST_Y_HUD);
		font.Draw(x + MAP_POS_X, y + MAP_POS_Y - ADJUST_Y_HUD, FillNumber(std::to_string(1), 1));
		font.Draw(x + SCORE_POS_X, y + SCORE_POS_Y- ADJUST_Y_HUD, FillNumber(std::to_string(mario->GetCoin()), 7)); // chua co ham get score nen sai tam
		font.Draw(x + COIN_POS_X, y + COIN_POS_Y- ADJUST_Y_HUD, FillNumber(std::to_string(mario->GetCoin()), 2));
		font.Draw(x + TIME_POS_X, y + TIME_POS_Y- ADJUST_Y_HUD, FillNumber(std::to_string(remainingTime), 3));
		/*font.Draw(x + LIVE_POS_X, y + LIVE_POS_Y, FillNumber(std::to_string(3), 1));*/
		LPTEXTURE TexPatch = CTextures::GetInstance()->Get(35);
		/*LPSPRITE SpriteTileLogo = new CSprite(0, 8, 50, 24, 57, TexPatch);*/
		//SpriteTileLogo->Draw(x + LOGO_POS_X, y + LOGO_POS_Y);
		if (mario->isRunning || mario->isFlying)
		{
			
			if (mario->runningStack >= 1)
			{
				DrawPowerBar(x + RUNNING_STACK_1_POS_X, y + RUNNING_STACK_POS_Y- ADJUST_Y_HUD);
			}
			if (mario->runningStack >= 2)
			{
				DrawPowerBar(x + RUNNING_STACK_2_POS_X, y + RUNNING_STACK_POS_Y- ADJUST_Y_HUD);
			}
			if (mario->runningStack >= 3)
			{
				DrawPowerBar(x + RUNNING_STACK_3_POS_X, y + RUNNING_STACK_POS_Y- ADJUST_Y_HUD);
			}
			if (mario->runningStack >= 4)
			{
				DrawPowerBar(x + RUNNING_STACK_4_POS_X, y + RUNNING_STACK_POS_Y- ADJUST_Y_HUD);
			}
			if (mario->runningStack >= 5)
			{
				DrawPowerBar(x + RUNNING_STACK_5_POS_X, y + RUNNING_STACK_POS_Y- ADJUST_Y_HUD);
			}
			if (mario->runningStack >= 6)
			{
				DrawPowerBar(x + RUNNING_STACK_6_POS_X, y + RUNNING_STACK_POS_Y- ADJUST_Y_HUD);
			}
			if (abs(mario->vx) == 0.3f)
			{
				LPSPRITE SpriteTilePower = new CSprite(0, 12, 33, 27, 40, TexPatch);
				SpriteTilePower->Draw(x + RUNNING_STACK_7_POS_X, y + RUNNING_STACK_POS_Y- ADJUST_Y_HUD);
			}
		}
	}
	else {
		Sprite->Draw(x + HUD_POS_X, y + HUD_POS_Y);
		font.Draw(x + MAP_POS_X, y + MAP_POS_Y, FillNumber(std::to_string(1), 1));
		font.Draw(x + SCORE_POS_X, y + SCORE_POS_Y, FillNumber(std::to_string(mario->GetCoin()), 7)); // chua co ham get score nen sai tam
		font.Draw(x + COIN_POS_X, y + COIN_POS_Y, FillNumber(std::to_string(mario->GetCoin()), 2));
		font.Draw(x + TIME_POS_X, y + TIME_POS_Y, FillNumber(std::to_string(remainingTime), 3));
		/*font.Draw(x + LIVE_POS_X, y + LIVE_POS_Y, FillNumber(std::to_string(3), 1));*/
		LPTEXTURE TexPatch = CTextures::GetInstance()->Get(35);
		/*LPSPRITE SpriteTileLogo = new CSprite(0, 8, 50, 24, 57, TexPatch);*/
		//SpriteTileLogo->Draw(x + LOGO_POS_X, y + LOGO_POS_Y);
		if (mario->isRunning || mario->isFlying)
		{
		
			if (mario->runningStack >= 1)
			{
				DrawPowerBar(x + RUNNING_STACK_1_POS_X, y + RUNNING_STACK_POS_Y);
			}
			if (mario->runningStack >= 2)
			{
				DrawPowerBar(x + RUNNING_STACK_2_POS_X, y + RUNNING_STACK_POS_Y);
			}
			if (mario->runningStack >= 3)
			{
				DrawPowerBar(x + RUNNING_STACK_3_POS_X, y + RUNNING_STACK_POS_Y);
			}
			if (mario->runningStack >= 4)
			{
				DrawPowerBar(x + RUNNING_STACK_4_POS_X, y + RUNNING_STACK_POS_Y);
			}
			if (mario->runningStack >= 5)
			{
				DrawPowerBar(x + RUNNING_STACK_5_POS_X, y + RUNNING_STACK_POS_Y);
			}
			if (mario->runningStack >= 6)
			{
				DrawPowerBar(x + RUNNING_STACK_6_POS_X, y + RUNNING_STACK_POS_Y);
			}
			if (abs(mario->vx) == 0.3f)
			{
				LPSPRITE SpriteTilePower = new CSprite(0, 12, 33, 27, 40, TexPatch);
				SpriteTilePower->Draw(x + RUNNING_STACK_7_POS_X, y + RUNNING_STACK_POS_Y);
			}
		}
	}
}

void HUD::DrawPowerBar(float X, float Y) {
	LPTEXTURE TexPatch = CTextures::GetInstance()->Get(ID_TEXT_FONT_POWER);
	LPSPRITE SpriteTile = new CSprite(0, 3, 33, 11, 40, TexPatch);
	SpriteTile->Draw(X - 1, Y);
}
