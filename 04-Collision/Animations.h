#pragma once
#include "Animation.h"
#include "Sprite.h"
#include <unordered_map>
#include <d3dx10.h>
#include <Windows.h>

class CAnimations
{
	static CAnimations* __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();
	static CAnimations* GetInstance();
};

