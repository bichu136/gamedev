#include "PlayableCharacter.h"
#include "GlobalDefine.h"
#include "QuestionBlock.h"
#include "WoodenFloor.h"
#include "debug.h"
#include "Goomba.h"
#include "RedKooba.h"
#include "LoadedResources.h"
#include "Box.h"
#define MARIO_MAX_VELOCITY_WALK 6.0f
#define MARIO_MAX_VELOCITY_RUN 14.0f
#define MARIO_ACCELARATION_WALK 0.5f
#define MARIO_ACCELARATION_RUN 0.7f
#define GRAVITY -0.6f
void PlayableCharacter::tryToAttack()
{
	//LoadedResources* lr = LoadedResources::getInstance();
	switch (powerUpLevel) {
	case 2:
		createAttackFire();
		break;
	case 3:
		createAttackTanuki();
		break;
	case 0:
	case 1:
		break;
	}
	DebugOutTitle(L"%d", powerUpLevel);
}
PlayableCharacter::PlayableCharacter(float x, float y):GameObject(x,y)
{
	vx = 0.0f;
	vy = 0.0f;
	ax = 0.0f;
	ay = GRAVITY;
	canNormalJump = true;
	state = SMALL_MARIO_STATE_IDLE_LEFT;
	powerUpLevel = 0;
}

int PlayableCharacter::getAnimationSmall()
{
	if (vy <= 0.0f && vy >= -1.0f) {
		
	}
	else {
		if (vx > 0) {
			state = SMALL_MARIO_STATE_AIR_RIGHT;
			return SMALL_MARIO_STATE_AIR_RIGHT;

		}
		else if (vx < 0 ){
			state = SMALL_MARIO_STATE_AIR_LEFT;
			return SMALL_MARIO_STATE_AIR_LEFT;
		}
		if (state % 2 == 0) {
			state = SMALL_MARIO_STATE_AIR_LEFT;
			return state;
		}
		else {
			state = SMALL_MARIO_STATE_AIR_RIGHT;
			return state;
		}
		
	}


	if (vx * ax < 0) {
		if (vx > 0) {
			state = SMALL_MARIO_STATE_BRAKE_RIGHT;
			return SMALL_MARIO_STATE_BRAKE_RIGHT;

		}
		else if(vx<0) {
			state = SMALL_MARIO_STATE_BRAKE_LEFT;
			return SMALL_MARIO_STATE_BRAKE_LEFT;
		}
		return state;
	}
	if (abs(vx) > MARIO_MAX_VELOCITY_WALK) {
		if (vx > 0) {
			state = SMALL_MARIO_STATE_RUN_RIGHT;
			return SMALL_MARIO_STATE_RUN_RIGHT;
		}
		else  if(vx < 0) {
			state = SMALL_MARIO_STATE_RUN_LEFT;
			return SMALL_MARIO_STATE_RUN_LEFT;
		}
		return state;
	}
	else {
		if (vx > 0) {
			state = SMALL_MARIO_STATE_WALK_RIGHT;
			return SMALL_MARIO_STATE_WALK_RIGHT;
		}
		if (vx < 0) {
			state = SMALL_MARIO_STATE_WALK_LEFT;
			return SMALL_MARIO_STATE_WALK_LEFT;
		}
		if (vx == 0.0f) {
			if (state == SMALL_MARIO_STATE_IDLE_LEFT)
				return SMALL_MARIO_STATE_IDLE_LEFT;
			if (state == SMALL_MARIO_STATE_IDLE_RIGHT)
				return SMALL_MARIO_STATE_IDLE_RIGHT;
		}
	}
	return state;
}

int PlayableCharacter::getAnimationBig()
{
	if (vy <= 0.0f && vy >= -1.0f) {

	}
	else {
		if (vx > 0) {
			state = BIG_MARIO_STATE_AIR_RIGHT;
			return BIG_MARIO_STATE_AIR_RIGHT;

		}
		else if (vx < 0) {
			state = BIG_MARIO_STATE_AIR_LEFT;
			return BIG_MARIO_STATE_AIR_LEFT;
		}
		if (state % 2 == 0) {
			state = BIG_MARIO_STATE_AIR_LEFT;
			return state;
		}
		else {
			state = BIG_MARIO_STATE_AIR_RIGHT;
			return state;
		}

	}


	if (vx * ax < 0) {
		if (vx > 0) {
			return BIG_MARIO_STATE_BRAKE_RIGHT;

		}
		else {
			return BIG_MARIO_STATE_BRAKE_LEFT;
		}
	}
	if (abs(vx) > MARIO_MAX_VELOCITY_WALK) {
		if (vx > 0) {
			return BIG_MARIO_STATE_RUN_RIGHT;
		}
		else {
			return BIG_MARIO_STATE_RUN_LEFT;
		}
	}
	else {
		if (vx > 0) {
			return BIG_MARIO_STATE_WALK_RIGHT;
		}
		if (vx < 0) {
			return BIG_MARIO_STATE_WALK_LEFT;
		}
		if (vx == 0.0f) {
			if (state == SMALL_MARIO_STATE_IDLE_LEFT)
				return BIG_MARIO_STATE_IDLE_LEFT;
			if (state == SMALL_MARIO_STATE_IDLE_RIGHT)
				return BIG_MARIO_STATE_IDLE_RIGHT;
		}
	}
	return BIG_MARIO_STATE_AIR_LEFT;
}

int PlayableCharacter::getAnimationFire()
{
	if (vy <= 0.0f && vy >= -1.0f) {

	}
	else {
		if (vx > 0) {
			state = FIRE_MARIO_STATE_AIR_RIGHT;
			return FIRE_MARIO_STATE_AIR_RIGHT;

		}
		else if (vx < 0) {
			state = FIRE_MARIO_STATE_AIR_LEFT;
			return FIRE_MARIO_STATE_AIR_LEFT;
		}
		if (state % 2 == 0) {
			state = FIRE_MARIO_STATE_AIR_LEFT;
			return state;
		}
		else {
			state = FIRE_MARIO_STATE_AIR_RIGHT;
			return state;
		}

	}


	if (vx * ax < 0) {
		if (vx > 0) {
			return FIRE_MARIO_STATE_BRAKE_RIGHT;

		}
		else {
			return FIRE_MARIO_STATE_BRAKE_LEFT;
		}
	}
	if (abs(vx) > MARIO_MAX_VELOCITY_WALK) {
		if (vx > 0) {
			return FIRE_MARIO_STATE_RUN_RIGHT;
		}
		else {
			return FIRE_MARIO_STATE_RUN_LEFT;
		}
	}
	else {
		if (vx > 0) {
			return FIRE_MARIO_STATE_WALK_RIGHT;
		}
		if (vx < 0) {
			return FIRE_MARIO_STATE_WALK_LEFT;
		}
		if (vx == 0.0f) {
			if (state == SMALL_MARIO_STATE_IDLE_LEFT)
				return FIRE_MARIO_STATE_IDLE_LEFT;
			if (state == SMALL_MARIO_STATE_IDLE_RIGHT)
				return FIRE_MARIO_STATE_IDLE_RIGHT;
		}
	}
	return FIRE_MARIO_STATE_AIR_LEFT;
}

int PlayableCharacter::getAnimationTanuki()
{
	if (vy <= 0.0f && vy >= -1.0f) {

	}
	else {
		if (vx > 0) {
			state = TANUKI_MARIO_STATE_AIR_RIGHT;
			return TANUKI_MARIO_STATE_AIR_RIGHT;

		}
		else if (vx < 0) {
			state = TANUKI_MARIO_STATE_AIR_LEFT;
			return TANUKI_MARIO_STATE_AIR_LEFT;
		}
		if (state % 2 == 0) {
			state = TANUKI_MARIO_STATE_AIR_LEFT;
			return state;
		}
		else {
			state = TANUKI_MARIO_STATE_AIR_RIGHT;
			return state;
		}

	}


	if (vx * ax < 0) {
		if (vx > 0) {
			return TANUKI_MARIO_STATE_BRAKE_RIGHT;

		}
		else {
			return TANUKI_MARIO_STATE_BRAKE_LEFT;
		}
	}
	if (abs(vx) > MARIO_MAX_VELOCITY_WALK) {
		if (vx > 0) {
			return TANUKI_MARIO_STATE_RUN_RIGHT;
		}
		else {
			return TANUKI_MARIO_STATE_RUN_LEFT;
		}
	}
	else {
		if (vx > 0) {
			return TANUKI_MARIO_STATE_WALK_RIGHT;
		}
		if (vx < 0) {
			return TANUKI_MARIO_STATE_WALK_LEFT;
		}
		if (vx == 0.0f) {
			if (state == SMALL_MARIO_STATE_IDLE_LEFT)
				return TANUKI_MARIO_STATE_IDLE_LEFT;
			if (state == SMALL_MARIO_STATE_IDLE_RIGHT)
				return TANUKI_MARIO_STATE_IDLE_RIGHT;
		}
	}
	return TANUKI_MARIO_STATE_AIR_LEFT;
}

void PlayableCharacter::Update(DWORD dt)
{
	if (state == MARIO_STATE_DIE) {
		vx = 0;
		ax = 0;
		vy = 0;
		ay = 0;
	}
	//TODO: if in attack state
	// still update x and y but state not change.
	//canNormalJump = false;
	ay = GRAVITY;
	float pre_vx = vx;
	vy += ay;
	vx += ax;
	//if (state == SMALL_MARIO_STATE_IDLE_LEFT) {
	//	if (vx * pre_vx <= 0.0f) vx = 0.0f;
	//}
	//if (state == SMALL_MARIO_STATE_IDLE_RIGHT) {
	//	if (vx * pre_vx <= 0.0f) vx = 0.0f;
	//}
	if (abs(vx) > abs(maxVx)) vx = vx>0? maxVx: -maxVx;
	//check collision
	//DebugOutTitle(L"%0.3f,%0.3f", this->x, this->y);
	
	isOnPlatform = false;
	
	//Collistion::getInstance->process(this);
 }

int PlayableCharacter::GetAnimationID(int i)
{
	return 0;
}

int PlayableCharacter::getCorrectAnimation()
{
	//return SMALL_MARIO_STATE_IDLE_LEFT;
	if (state == MARIO_STATE_DIE)
		return 100;
	switch (powerUpLevel) {
	case 1:
		return getAnimationBig();
	case 2:
		return getAnimationFire();
	case 3:
		return getAnimationTanuki();
	case 0:
		return getAnimationSmall();
	}
	
	
}

 void PlayableCharacter::walk(int dir) {

	 if (state == MARIO_STATE_DIE)
		 return;
	 if (dir == LEFT) {
		 this->_setState(SMALL_MARIO_STATE_WALK_LEFT);
	 }
	 if (dir == RIGHT) {
		 this->_setState(SMALL_MARIO_STATE_WALK_RIGHT);
	 }
 }
 void PlayableCharacter::run(int dir)
 {
	 if (state == MARIO_STATE_DIE)
		 return;
	 if (dir == LEFT) {
		 this->_setState(SMALL_MARIO_STATE_RUN_LEFT);
	 }
	 if (dir == RIGHT) {
		 this->_setState(SMALL_MARIO_STATE_RUN_RIGHT);
	 }
	 //change property + change state for rendering
 }

 void PlayableCharacter::jump()
 {
	 //change property + change state for rendering
	 //checkground
	 if (!canNormalJump) {
		 return;
	 }
	 if (state == MARIO_STATE_DIE)
		 return;
	 if (state % 2 == 0) {
		 this->_setState(SMALL_MARIO_STATE_AIR_LEFT);
	 }
	 else {
		 this->_setState(SMALL_MARIO_STATE_AIR_RIGHT);
	 }
	 canNormalJump = false;
	 
	 
	 
	 //gravity;
	 //ay = -0.1f;
 }

 void PlayableCharacter::releaseJump()
 {
	 if (state == MARIO_STATE_DIE)
		 return;
	 if (vy>3.0f )vy = 3.0f;
	 return;
 }

 void PlayableCharacter::slowDown()
 {
	 if (state == MARIO_STATE_DIE)
		 return;
	 if (vx == 0.0f) { return; }
	 if (vx > 0) {
		 this->_setState(SMALL_MARIO_STATE_IDLE_RIGHT);

	 }
	 else {
		 this->_setState(SMALL_MARIO_STATE_IDLE_LEFT);
	 }
 }

 void PlayableCharacter::brake(int dir)
 {
	 //change property + change state for rendering
	 //ax = -0.1f;
	 //ax = -ax* 0.7f;
 }
 void PlayableCharacter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
 {
	 if (powerUpLevel == 0) {
		 left = x - SMALL_MARIO_WIDTH * SCALE_WIDTH / 2;
		 right = left + SMALL_MARIO_WIDTH * SCALE_WIDTH;
		 top = y - SMALL_MARIO_HEIGHT * SCALE_HEIGHT / 2;
		 bottom = top + SMALL_MARIO_HEIGHT * SCALE_HEIGHT;
	 }
	 else {
		 left = x - BIG_MARIO_WIDTH * SCALE_WIDTH / 2;
		 right = left + BIG_MARIO_WIDTH * SCALE_WIDTH;
		 top = y - BIG_MARIO_HEIGHT * SCALE_HEIGHT / 2;
		 bottom = top + BIG_MARIO_HEIGHT * SCALE_HEIGHT;
	 }
	 

 }
 void PlayableCharacter::onCollisionWithEnemy(CollisionEvent* e)
 {
	 if (dynamic_cast<Goomba*>(e->des)) {
		 Goomba* interact_with = dynamic_cast<Goomba*>(e->des);
		 if (interact_with->isCollidable()) {
			 if (e->ny >= 1.0f) {
				 interact_with->dead();
			 }
			 else {
				 this->dead();
			 }
			 canNormalJump = true;
			 jump();
			 return;
		 }

	 }
	 if (dynamic_cast<RedKooba*>(e->des)) {
		 RedKooba* interact_with = dynamic_cast<RedKooba*>(e->des);
		 if (interact_with->isCollidable()) {
			 if (interact_with->getState() == 0|| interact_with->getState()== 2) {
				 if (e->ny >= 1.0f) {
					 interact_with->dead();
				 }
				 else {
					 this->dead();
				 }
				 canNormalJump = true;
				 jump();
				 return;
			 }
			 if (interact_with->getState() == 1) {
				 float x, y;
				 e->des->GetPosition(x, y);
				 float dir = this->x - x;
				 interact_with->roll(dir);
			 }
			 
		 }
	 }

 }
 void PlayableCharacter::onCollisionWith(CollisionEvent* e,bool is_double_collision)
 {
	 if (!isCollidable()) return;
	 if (e->ny >= 1.0f && e->des->isBlockingTop())
	 {
		 y += e->t * vy + e->ny * 1.0f;
		 float block_left, block_top, block_right, block_bottom;
		 float this_left, this_top, this_right, this_bottom;
		 e->des->GetBoundingBox(block_left, block_top, block_right, block_bottom);
		 this->GetBoundingBox(this_left, this_top, this_right, this_bottom);
		 //DebugOutTitle(L"%0.3f,%0.3f,%0.3f", this->x, this->y, this->vx);
		 canNormalJump = true;
		 vy = 0.0f;
	 }
	 if (e->ny <= -1.0f && e->des->isBlockingBottom()) {
		 y += e->t * vy + e->ny * 1.0f;
		 vy = GRAVITY;
	 }
	 if (e->nx <= -1.0f && e->des->isBlockingLeft())
	 {
		 
		 x += e->t * vx + e->nx *1.0f;
		 vx = 0;
		 //OnNoCollision();
		 return;
	 }
	 if (e->nx >= 1.0f && e->des->isBlockingRight())
	 {
		 x += e->t * vx + e->nx * 1.0f;
		 vx = 0;
		 return;
	 }
	 if (dynamic_cast<QuestionBlock*>(e->des)) {
		 if (e->ny <= -1.0f) {
			 QuestionBlock* interact_with = dynamic_cast<QuestionBlock*>(e->des);
			 interact_with->active();
		 }
	 }
	 
	
	 /*if (dynamic_cast<WoodenFloor*>(e->des)) {
		 WoodenFloor* interact_with1 = dynamic_cast<WoodenFloor*>(e->des);
		 if (dynamic_cast<Box*>(interact_with1)) {
			 Box* interact_with = dynamic_cast<Box*>(interact_with1);
			 if (e->ny <= -1.0f) {
				 vy = 0.0f;
				 isOnPlatform = true;
				 canNormalJump = true;
			 }
		 }
		 else {
			 state = state;
		 }
	 }*/
}
 void PlayableCharacter::OnNoCollision()
 {
	 x += vx;
	 y += vy;
 }
 void PlayableCharacter::dead()
 {
	 state = MARIO_STATE_DIE;
 }
 void PlayableCharacter::_setState(int state) {
	 if (state == MARIO_STATE_DIE) 
		 return;
	 this->state = state;
	 switch (state) {
	 case SMALL_MARIO_STATE_RUN_RIGHT:
		 //if (isSitting) break;
		 maxVx = MARIO_MAX_VELOCITY_RUN;
		 ax = MARIO_ACCELARATION_RUN;
		 //nx = 1;
		 break;
	 case SMALL_MARIO_STATE_RUN_LEFT:
		 //if (isSitting) break;
		 maxVx = MARIO_MAX_VELOCITY_RUN;
		 ax = -MARIO_ACCELARATION_RUN;
		 //nx = -1;
		 break;
	 case SMALL_MARIO_STATE_WALK_RIGHT:
		 //if (isSitting) break;
		 maxVx = MARIO_MAX_VELOCITY_WALK;
		 ax = MARIO_ACCELARATION_WALK;
		 //nx = 1;
		 break;
	 case SMALL_MARIO_STATE_WALK_LEFT:
		 //if (isSitting) break;
		 maxVx = MARIO_MAX_VELOCITY_WALK;
		 ax = -MARIO_ACCELARATION_WALK;
		 //nx = -1;
		 break;
	 case SMALL_MARIO_STATE_IDLE_LEFT:
	 case SMALL_MARIO_STATE_IDLE_RIGHT:
		 ax = -0.0f;
		 vx = 0.0f;
		 break;
	 case SMALL_MARIO_STATE_AIR_RIGHT:
	 case SMALL_MARIO_STATE_AIR_LEFT:
		 if (abs(vx) > MARIO_MAX_VELOCITY_WALK) {
			 vy = 20.0f;
			 ay = GRAVITY;
		}
		 else {
			 vy = 18.0f;
			 ay = GRAVITY;
		 }
			
		 break;
	 }
	 //case MARIO_STATE_SIT:
		// //if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		// //{
		//	 state = MARIO_STATE_IDLE;
		//	 isSitting = true;
		//	 vx = 0; vy = 0.0f;
		//	 y += MARIO_SIT_HEIGHT_ADJUST;
		// //}
		// break;
	 

	 /*case MARIO_STATE_DIE:
		 vy = -MARIO_JUMP_DEFLECT_SPEED;
		 vx = 0;
		 ax = 0;
		 break;*/
 }

 void PlayableCharacter::createAttackFire()
 {
	 LoadedResources* lr = LoadedResources::getInstance();
	 //lr->Attack.push_back(new Fireball(x, y));
 }

 void PlayableCharacter::createAttackTanuki()
 {
	 LoadedResources* lr = LoadedResources::getInstance();
	 //lr->Attack.push_back(new tailwhip(x, y));
	 //state = TANUKI_ATTACK_STATE;
	 
 }
 
 void PlayableCharacter::AddAnimation(int id)
 {
	 return;
 }