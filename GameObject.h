#pragma once
#include"AnimationManage.h"
#include<windows.h>
class GameObject
{
protected:

	float x;
	float y;

	float vx;
	float vy;

	int nx;

	int state;

	bool isDeleted;

public:
	
	std::vector<int> animationIDList;
	GameObject(float x, float y) {
		this->x = x; this->y = y; 
		vx = 0;
		vy = 0;
		nx = 0;
		state = 0;
		isDeleted = false;
	}
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void GetPosition(float &x, float &y){ x = this->x, y = this->y; }
	float GetX() { return x; }
	float GetY() { return y; }

	virtual void Update(DWORD dt) = 0;
	virtual bool isBlocking() { return true; }
	virtual int GetAnimationID(int i) = 0;
	virtual void AddAnimation(int id) = 0;
	virtual int getCorrectAnimation() = 0;
	virtual bool isCollidable() { return false; }
	virtual void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
};

