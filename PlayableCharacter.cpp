#include "PlayableCharacter.h"
#include "GlobalDefine.h"
#include "debug.h"
#define MARIO_MAX_VELOCITY_WALK 3.0f
#define MARIO_MAX_VELOCITY_RUN 7.0f
#define MARIO_ACCELARATION_WALK 0.2f
#define MARIO_ACCELARATION_RUN 0.225f
#define GRAVITY -0.1f
PlayableCharacter::PlayableCharacter(float x, float y):GameObject(x,y)
{
	vx = 0.0f;
	vy = 0.0f;
	ax = 0.0f;
	ay = GRAVITY;
	canNormalJump = false;
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
			state = SMALL_MARIO_STATE_AIR_RIGHT;
			return SMALL_MARIO_STATE_AIR_RIGHT;

		}
		else if (vx < 0) {
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
	return getAnimationBig();
}

int PlayableCharacter::getAnimationTanuki()
{
	return getAnimationBig();
}

void PlayableCharacter::Update(DWORD dt)
{
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
	DebugOutTitle(L"%0.3f,%0.3f", this->x, this->y);
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

	 if (dir == LEFT) {
		 this->_setState(SMALL_MARIO_STATE_WALK_LEFT);
	 }
	 if (dir == RIGHT) {
		 this->_setState(SMALL_MARIO_STATE_WALK_RIGHT);
	 }
 }
 void PlayableCharacter::run(int dir)
 {
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
	 this->_setState(SMALL_MARIO_STATE_AIR);
	 
	 
	 //gravity;
	 //ay = -0.1f;
 }

 void PlayableCharacter::releaseJump()
 {
	 if (vy>3.0f )vy = 3.0f;
	 return;
 }

 void PlayableCharacter::slowDown()
 {
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
 void PlayableCharacter::onCollisionWith(CollisionEvent* e)
 {

	 if (e->ny != 0 && e->des->isBlocking())
	 {
		 vy = 0;
		 isOnPlatform = true;
		 canNormalJump = true;
	 }
	 else
		 if (e->nx != 0 && e->des->isBlocking())
		 {
			 vx = 0;
		 }
 }
 void PlayableCharacter::OnNoCollision()
 {
	 x += vx;
	 y += vy;
 }
 void PlayableCharacter::_setState(int state) {
	 if (state == MARIO_STATE_DIE) return;
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
	 case SMALL_MARIO_STATE_AIR:
	 case SMALL_MARIO_STATE_AIR_RIGHT:
	 case SMALL_MARIO_STATE_AIR_LEFT:
		 if (vx > MARIO_MAX_VELOCITY_WALK) {
			 vy = 10.0f;
			 ay = GRAVITY;
		}
		 else {
			 vy = 7.0f;
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
 
 void PlayableCharacter::AddAnimation(int id)
 {
	 return;
 }