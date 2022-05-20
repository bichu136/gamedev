#pragma once
#include"PlayableCharacter.h"
#include"Platform.h"
#include"WoodenFloor.h"
#include"Pipe.h"
#include"Goomba.h"
#include"QuestionBlock.h"
#include"SpriteManage.h"
#include "Box.h"
#include"TextureManager.h"
#include"AnimationManage.h"
#include"CollisionEvent.h"
#include<vector>
class LoadedResources
{
private:
	static LoadedResources* __instance;
	static void _SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float& t,
		float& nx,
		float& ny);
	static CollisionEvent* SweptAABB(
		GameObject* objSrc,
		DWORD dt,
		GameObject* objDest);
	void Scan(
		GameObject* objSrc,
		DWORD dt,
		std::vector<GameObject*> *objDests,
		std::vector<CollisionEvent*> &coEvents);

	void Filter(
		GameObject* objSrc,
		std::vector<CollisionEvent*>& coEvents,
		CollisionEvent* &colX,
		CollisionEvent* &colY,
		int filterBlock = 1,
		int filterX = 1,
		int filterY = 1);
	void loadMarioSprite();
	void createMarioAnimation();
	void createFireMarioAnimation();
	void createTanukiMarioAnimation();
	void createSmallMarioAnimation();
	void createBigMarioAnimation();
public:
	PlayableCharacter* Mario;
	std::vector<GameObject*> stage_blocks;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> Attack;
	bool playableCollision;
	static LoadedResources* getInstance();
	void checCollisionMarioToStageBlocks(DWORD dt);
	void checkCollisionEnemiesToStageBlocks(DWORD dt, GameObject* enemies);
	void LoadResources();
	void Update(DWORD dt);
	void checCollisionMarioToEnemies(DWORD dt);
};

