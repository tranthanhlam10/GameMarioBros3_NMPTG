#include "IntroGameKey.h"
#include "WorldPlayer.h"
#include "IntroGame.h"

#include "Pointer.h"

void IntroGameKey::OnKeyDown(int KeyCode)
{
	Pointer* pointer = (Pointer*)((LPINTROSCENE)CGame::GetInstance()->GetCurrentScene())->GetIntroPointer();

	switch (KeyCode)
	{
	case DIK_UP:
		if (pointer->GetY() != ARROW_POSITION_TOP) {
			pointer->SetPosition(ARROW_DEFAULT_POSITION_X, ARROW_POSITION_TOP);
		}
		break;
	case DIK_DOWN:
		if (pointer->GetY() != ARROW_POSITION_BOTTOM) {
			pointer->SetPosition(ARROW_DEFAULT_POSITION_X, ARROW_POSITION_BOTTOM);
		}
	case DIK_S:
		if (pointer->GetY() == ARROW_POSITION_TOP) {
			//CGame::GetInstance()->InitiateSwitchScene(WORLD_MAP_ID);
		}
		break;
	}
}