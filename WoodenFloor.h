#pragma once
#include "GameObject.h"
class WoodenFloor :
    public GameObject
{
protected:
	int sprite_1;
	int sprite_2;
	int sprite_3;
	int sprite_4;
	int sprite_5;
	int sprite_6;
	int sprite_7;
	int sprite_8;
	int sprite_9;
	int width;
	int height;
public:
	WoodenFloor(float x, float y, int width, int height);
	void Update(DWORD dt) {};
	bool isBlocking() { return true; }
	int GetAnimationID(int i) { return 0; }
	void AddAnimation(int id) { return; }
	int getCorrectAnimation() { return 0; }
	bool isCollidable() { return false; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int getCorrectSprite(int w_iter,int h_iter);
	void getSize(int &width, int &height) { width = this->width, height = this->height; }
	void getCorrectSpritePosition(int w_iter,int h_iter,float &x,float &y);
};

