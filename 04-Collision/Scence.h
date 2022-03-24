#pragma once
#include "KeyEventHandler.h"
#include <d3dx10.h>


class CScene // đại diện cho các cảnh có trong trò chơi, chú ý intro scene và end scene
{
protected:
	CKeyEventHandler* key_handler;
	int id;
	LPCWSTR sceneFilePath;

public:
	CScene(int id, LPCWSTR filePath);

	CKeyEventHandler* GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0; // tải scene
	virtual void Unload() = 0; // xóa dữ liệu của scene
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};
typedef CScene* LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler
{
protected:
	CScene* scence; // con trỏ để trỏ về 

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene* s) :CKeyEventHandler() { scence = s; }
}; 
