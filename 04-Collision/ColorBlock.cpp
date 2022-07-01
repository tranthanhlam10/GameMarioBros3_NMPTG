#include "ColorBlock.h"

#include "Mario.h"
#include "PlayScence.h"
#include "debug.h"
#include "Koopas.h"
CColorBlock::CColorBlock(float x, float y, float width, float height) : CGameObject(x, y) {

	this->width = width;
	this->height = height;
}

//int CColorBlock::IsBlocking()
//{
//	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
//   if (mario->isMoveOverBlockColor) {
//	   return 0;
//		return 1;
//	}
//}

void CColorBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y +1;	
}

