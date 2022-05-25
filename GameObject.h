#pragma once
#include"AnimationManage.h"
#include<windows.h>
#include "CollisionEvent.h"
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
	bool setPositioned;


public:
	bool is_delete;
	bool drawAtFront;
	std::vector<int> animationIDList;
	GameObject(float x, float y) {
		this->x = x; this->y = y; 
		vx = 0;
		vy = 0;
		nx = 0;
		state = 0;
		isDeleted = false;
		setPositioned = true;
	}
	void SetPosition(float x, float y) {
		if (!setPositioned) { 
			this->x = x;
			this->y = y; 
		} 
	}
	virtual void GetPosition(float &x, float &y){ x = this->x, y = this->y; }
	float GetX() { return x; }
	float GetY() { return y; }

	virtual void Update(DWORD dt) = 0;
	virtual bool isBlockingRight() { return true; }
	virtual bool isBlockingLeft() { return true; }
	virtual bool isBlockingTop() { return true; }
	virtual bool isBlockingBottom() { return true; }
	virtual int GetAnimationID(int i) = 0;
	virtual void AddAnimation(int id) = 0;
	virtual int getCorrectAnimation() = 0;
	virtual void onCollisionWith(CollisionEvent* e, bool is_double_collision = true) { return; };
	virtual void OnNoCollision() { x += vx; y += vy; }
	virtual bool isCollidable() { return false; }
	virtual void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; };
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
};

