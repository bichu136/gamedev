#pragma once
#include "GameObject.h"
class Leaf :
	public GameObject
{

private:
	bool is_spawning;
	int spawn_frame;
	int dead_frame;
	bool isOnPlatform;
	float vx;
	int velocity_determine;
	float ax;
	float vy;
public:
	Leaf(float x, float y);
	void Update(DWORD dt);
	bool isBlocking() { return false; }
	bool isCollidable() { return false; }
	int GetAnimationID(int i);
	void AddAnimation(int id);
	int getCorrectAnimation();
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void dead();
	void onCollisionWith(CollisionEvent* e, bool is_double_collision);
	void onCollisionWith(CollisionEvent* e);
	void OnNoCollision();

};

