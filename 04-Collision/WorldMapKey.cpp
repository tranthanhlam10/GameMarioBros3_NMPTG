#include "WorldMapKey.h"
#include "WorldPlayer.h"
#include "WorldScene.h"
#include "debug.h"

void WorldMapKey::OnKeyDown(int KeyCode)
{
	WorldPlayer* player = (WorldPlayer*)((LPWORLDSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_S:
	{
		if (player->sceneSwitch != -1 && player->sceneSwitch != 0) {
			CGame::GetInstance()->SwitchScene(player->sceneSwitch);
			player->sceneSwitch = -1;
			
		}
		break;
	}
	case DIK_RIGHT:
		if (player->allowRight) {
			player->SetState(MARIO_WORLD_MAP_STATE_WALK_RIGHT);
			player->allowLeft = false;
			player->allowRight = false;
			player->allowTop = false;
			player->allowBottom = false;
		}
		break;
	case DIK_LEFT:
		if (player->allowLeft)
		{
			player->SetState(MARIO_WORLD_MAP_STATE_WALK_LEFT);
			player->allowLeft = false;
			player->allowRight = false;
			player->allowTop = false;
			player->allowBottom = false;
		}
		break;
	case DIK_UP:
		if (player->allowTop) {
			player->SetState(MARIO_WORLD_MAP_STATE_WALK_TOP);
			player->allowLeft = false;
			player->allowRight = false;
			player->allowTop = false;
			player->allowBottom = false;
		}
		break;
	case DIK_DOWN:
		if (player->allowBottom) {
			player->SetState(MARIO_WORLD_MAP_STATE_WALK_BOTTOM);
			player->allowLeft = false;
			player->allowRight = false;
			player->allowTop = false;
			player->allowBottom = false;
		}
		break;
	
	}
}


