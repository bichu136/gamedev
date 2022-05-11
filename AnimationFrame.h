#pragma once
#include"sprite.h"
class AnimationFrame
{
	Sprite* sprite;
	DWORD time;
public:
	AnimationFrame(Sprite* sprite, DWORD time) { this->sprite = sprite, this->time = time; }
	DWORD GetTime() { return time; }
	
	Sprite* getSprite() { return sprite; }
};

