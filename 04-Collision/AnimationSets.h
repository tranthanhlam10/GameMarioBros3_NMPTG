#pragma once

#include <unordered_map>
#include "Animations.h"
#include"Animation.h"
#include <d3dx10.h>
#include "Sprite.h"
#include <Windows.h>



typedef vector<LPANIMATION> CAnimationSet;

typedef CAnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class CAnimationSets 
{

	static CAnimationSets* __instance; // vấn đề nằm ở chỗ khai báo dòng lệnh này, compiler không nhân được

	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);
	static CAnimationSets* GetInstance();
};

