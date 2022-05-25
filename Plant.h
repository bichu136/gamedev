#pragma once
#include "GameObject.h"
#include"CollisionEvent.h"
#include"Box.h"
class Plant :
	public GameObject
{
private:
	bool is_dead;
	bool is_collide;
	int dead_frame;
	bool isOnPlatform;
	int OnFrame;
	int OffFrame;
	bool isOn;
	bool isOff;
	float origin_x;
	float origin_y;
public:
	Plant(float x, float y);
	void Update(DWORD dt);
	bool isBlocking() { return false; }
	int GetAnimationID(int i);
	void AddAnimation(int id);
	int getCorrectAnimation();
	bool isCollidable() { return !is_dead; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void dead();
	void onCollisionWith(CollisionEvent* e, bool is_double_collision);
	void onCollisionWith(CollisionEvent* e);
	void OnNoCollision();

};

