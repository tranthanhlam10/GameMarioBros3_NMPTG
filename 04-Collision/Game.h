#pragma once
#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "Texture.h"
#include "KeyEventHandler.h"
#include <unordered_map>
#include "Scence.h"
#include<string>
#include<string.h>

using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256

/*
	Our simple game framework
*/
class CGame
{
	static CGame* __instance;
	HWND hWnd;									// Window handle

	int backBufferWidth = 0;					// Backbuffer width & height, will be set during Direct3D initialization
	int backBufferHeight = 0;

	ID3D10Device* pD3DDevice = NULL;  //Direct30 device
	IDXGISwapChain* pSwapChain = NULL;
	ID3D10RenderTargetView* pRenderTargetView = NULL;
	ID3D10BlendState* pBlendStateAlpha = NULL;			// To store alpha blending state

	LPD3DX10SPRITE spriteObject;						// Sprite handling object, BIG MYSTERY: it has to be in this place OR will lead to access violation in D3D11.dll ????

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[KEYBOARD_STATE_SIZE];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	float cam_x = 0.0f;
	float cam_y = 0.0f;


	int screen_width;
	int screen_height;


	unordered_map<int, LPSCENE> scenes;
	int current_scene;

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);

	HINSTANCE hInstance;

	ID3D10SamplerState* pPointSamplerState;

public:
	// Init DirectX, Sprite Handler
	void Init(HWND hWnd, HINSTANCE hInstance);

	//
	// Draw a portion or ALL the texture at position (x,y) on the screen. (x,y) is at the CENTER of the image
	// rect : if NULL, the whole texture will be drawn
	//        if NOT NULL, only draw that portion of the texture 
	void Draw(float x, float y, LPTEXTURE tex, RECT* rect = NULL, float alpha = 1.0f);

	void Draw(float x, float y, LPTEXTURE tex, int l, int t, int r, int b, float alpha = 1.0f) // vẽ object lên vị trí xy
	{
		RECT rect;
		rect.left = l;
		rect.top = t;
		rect.right = r;
		rect.bottom = b;
		this->Draw(x, y, tex, &rect, alpha);
	}

	LPTEXTURE LoadTexture(LPCWSTR texturePath); // load các texture lên chương trình

	// Keyboard related functions 
	void InitKeyboard(LPKEYEVENTHANDLER handler); // khởi tạo bàn phím +
	int IsKeyDown(int KeyCode); // phím có được nhấn hay không+
	void ProcessKeyboard(); // xử lí bản phím+
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }   // khởi tại keyhandler+
	ID3D10Device* GetDirect3DDevice() { return this->pD3DDevice; }
	IDXGISwapChain* GetSwapChain() { return this->pSwapChain; }
	ID3D10RenderTargetView* GetRenderTargetView() { return this->pRenderTargetView; }

	ID3DX10Sprite* GetSpriteHandler() { return this->spriteObject; }

	ID3D10BlendState* GetAlphaBlending() { return pBlendStateAlpha; };


	void Load(LPCWSTR gameFile);
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(int scene_id);

	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }


	int GetBackBufferWidth() { return backBufferWidth; }
	int GetBackBufferHeight() { return backBufferHeight; }

	static CGame* GetInstance();

	void SetPointSamplerState();
	int GetScene() { return current_scene; }
	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; } // set vị trí của camera

	float GetCamX() { return cam_x; }
	float GetCamY() { return cam_y; }
	void GetCamPos(float& x, float& y) { x = cam_x; y = cam_y; } // lấy vị trí của camera

	~CGame();
};

typedef CGame* LPGAME;
