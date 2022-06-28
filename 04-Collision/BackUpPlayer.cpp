#include "BackUpPlayer.h"
#include "PlayScence.h"

BackUpPlayer* BackUpPlayer::__instance = NULL;
BackUpPlayer* BackUpPlayer::GetInstance()
{
	if (__instance == NULL)
	__instance = new BackUpPlayer();
	return __instance;
}

void BackUpPlayer::BackUpMario(CMario* mario)
{
	//health = mario->GetHealth();
	//score = mario->GetScore();
	level = mario->GetLevel();
	coin = mario->GetCoin();
	gameTime = ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetGameTime();
}

void BackUpPlayer::LoadBackUp(CMario* mario)
{
	//mario->SetHealth(health);
	//mario->SetScore(score);
	mario->SetLevel(level);
	mario->SetCoin(coin);
	((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->SetGameTime(gameTime);
}
