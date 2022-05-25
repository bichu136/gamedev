#pragma once
#include "GameObject.h"
#include "PlayableCharacter.h"
class TanukiAttack :
    public GameObject
{
private:
    PlayableCharacter* host;
    bool is_active = true;
    bool is_done = false;
public:
	TanukiAttack(float x, float y);
	void Update(DWORD dt);
	bool isBlocking() { return false; }
	int GetAnimationID(int i);
	void AddAnimation(int id);
	int getCorrectAnimation();
	bool isCollidable() { return true; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; };
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void dead();
	void onCollisionWith(CollisionEvent* e, bool is_double_collision);
	void onCollisionWith(CollisionEvent* e);
	void OnNoCollision();

};

