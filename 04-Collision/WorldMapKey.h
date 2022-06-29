#pragma once


#include "Scence.h"

class WorldMapKey : public CScenceKeyHandler
{
	CScene* scene;
public:
	virtual void OnKeyDown(int KeyCode);
	virtual void KeyState(BYTE* states) {};
	virtual void OnKeyUp(int KeyCode) {};
	WorldMapKey(LPSCENE s) :CScenceKeyHandler(s) { scene = s; }
};

