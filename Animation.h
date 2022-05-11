#pragma once
#include <Windows.h>
#include <unordered_map>
#include "Sprite.h"
//#include "AnimationFrame.h"
class Animation
{
	ULONGLONG lastFrameTime;
	int defaultTime;
	int currentFrame;
	std::vector<int> spriteIDList;
	std::vector<DWORD> timeforSpriteList;
public:
	Animation(int defaultT=0){ lastFrameTime = -1; currentFrame = -1; }
	void Add(int spriteID,DWORD time);
	void Add(int spriteID);
	int getCorrectSpriteID();
};

