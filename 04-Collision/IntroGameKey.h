#pragma once
#include "Scence.h"

#define ARROW_POSITION_TOP 175

#define ARROW_POSITION_BOTTOM 192

#define ARROW_DEFAULT_POSITION_X 90
#define  WORLDMAP						3
class IntroGameKey : public CScenceKeyHandler
{
	CScene* scene;
public:
	virtual void OnKeyDown(int KeyCode);
	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyUp(int KeyCode) {};
	IntroGameKey(LPSCENE s) : CScenceKeyHandler(s) { scene = s; }
};

