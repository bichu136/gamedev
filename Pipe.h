#pragma once
#include "GameObject.h"
#include "WoodenFloor.h"
class Pipe :
    public WoodenFloor
{
private:
    int size; //>2
    int orientation;
public:
	Pipe(float x, float y,int orientation,int size);
	//void active();
	int getCorrectAnimationID();
	int GetAnimationID(int i);
	void AddAnimation(int id);
	void Update(DWORD dt);
	//int GetAnimationID(int id);
	int getCorrectAnimation();
	int getCorrectSprite(int w_iter, int h_iter);
	//void AddAnimation(int id);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

