#pragma once
#include "WoodenFloor.h"
class Box :
    public WoodenFloor
{
private:
	
public:
	Box(float x, float y, int width, int height,int box_color);
	//void active();
	bool isBlockingLeft() { return false; }
	bool isBlockingRight() { return false; }
	bool isBlockingBottom() { return false; }
	int getCorrectAnimationID();
	int GetAnimationID(int i);
	void AddAnimation(int id);
	void Update(DWORD dt);
	//int GetAnimationID(int id);
	//bool isCollidable();
	int getCorrectAnimation();
	int getCorrectSprite(int w_iter, int h_iter);
	bool isBlocking() { return true; };
	//void AddAnimation(int id);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

