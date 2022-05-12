#pragma once
#include "GameObject.h"
#include "AnimationManage.h"
#include "GlobalDefine.h"
#include "CollisionEvent.h"
class PlayableCharacter :public GameObject
{
private: 
	float ax;
	float ay;
	bool isOnPlatform;
	bool canNormalJump;
	float maxVx;
	int powerUpLevel;
	//float maxVy;
	/*std::vector<int> animationIDList;*/
	//AnimationManage animationManage;
	void _setState(int state);
public:
	
	PlayableCharacter(float x, float y);
	int getAnimationSmall();
	int getAnimationBig();
	int getAnimationFire();
	int getAnimationTanuki();
	void Update(DWORD dt);
	void setPowerUplevel(int lvl) { this->powerUpLevel = lvl; y += 10.0f; }
	int GetAnimationID(int i);
	int getCorrectAnimation();
	void AddAnimation(int id);
	void walk(int dir);
	void beginRun();
	void run(int dir);
	void jump();
	void releaseJump();
	void slowDown();
	void brake(int dir);
	bool isCollidable() { return state != MARIO_STATE_DIE; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void onCollisionWith(CollisionEvent* e);
	/*void GetPosition(float& x, float& y);
	void SetPosition(float x, float y);*/
	void OnNoCollision();
	~PlayableCharacter();
};

