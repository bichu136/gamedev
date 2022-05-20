#pragma once
#include "GameObject.h"
#include "CollisionEvent.h"
class RedKooba :
    public GameObject
{
private:
	bool is_dead;
	int dead_frame;
	bool isOnPlatform;
	float vx;
	float vy;
	int state;
	bool not_fall;
public:
	RedKooba(float x, float y);
	void Update(DWORD dt);
	void roll(float dir) {
		state = 2;
		not_fall = false;
		if (dir >= 0) {
			vx = -7.0f;
		}
		else {
			vx = 7.0f;
		}
	}
	bool isBlocking() { return false; }
	int GetAnimationID(int i);
	void AddAnimation(int id);
	int getCorrectAnimation();
	bool isCollidable() { return !is_dead; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void dead();
	void onCollisionWith(CollisionEvent* e, bool is_double_collision);
	//void onCollisionWith(CollisionEvent* e);
	int getState() { return state; }
	void OnNoCollision();

};

