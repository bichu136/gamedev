#include "PlayableCharacter.h"
#include "GlobalDefine.h"
#include "debug.h"
#define MARIO_MAX_VELOCITY_WALK 2.0f
#define MARIO_MAX_VELOCITY_RUN 4.0f
#define MARIO_ACCELARATION_WALK 1.0f
#define MARIO_ACCELARATION_RUN 1.5f
PlayableCharacter::PlayableCharacter(float x, float y):GameObject(x,y)
{
	vx = 0.0f;
	vy = 0.0f;
	ax = 0.0f;
	ay = -0.1f;
	state = MARIO_STATE_IDLE_LEFT;
}

void PlayableCharacter::Update(DWORD dt)
{
	float pre_vx = vx;
	vy += ay;
	vx += ax;
	//if (state == MARIO_STATE_IDLE_LEFT) {
	//	if (vx * pre_vx <= 0.0f) vx = 0.0f;
	//}
	//if (state == MARIO_STATE_IDLE_RIGHT) {
	//	if (vx * pre_vx <= 0.0f) vx = 0.0f;
	//}
	if (abs(vx) > abs(maxVx)) vx = vx>0? maxVx: -maxVx;
	//check collision
	isOnPlatform = false;
	DebugOutTitle(L"%0.3f,%0.3f",this->x,this->y);
	//Collistion::getInstance->process(this);
 }

int PlayableCharacter::GetAnimationID(int i)
{
	return 0;
}

int PlayableCharacter::getCorrectAnimation()
{
	//return MARIO_STATE_IDLE_LEFT;
	if (vx * ax < 0) {
		if (vx > 0) {
			return MARIO_STATE_BRAKE_RIGHT;
			
		}
		else {
			return MARIO_STATE_BRAKE_LEFT;
		}
	}
	if (abs(vx) > MARIO_MAX_VELOCITY_WALK) {
		if (vx > 0) {
			return MARIO_STATE_RUN_RIGHT;
		}
		else {
			return MARIO_STATE_RUN_LEFT;
		}
	}
	else {
		if (vx > 0) {
			return MARIO_STATE_WALK_RIGHT;
		}
		if(vx <0) {
			return MARIO_STATE_WALK_LEFT;
		}
		if (vx == 0.0f) {
			if (state == MARIO_STATE_IDLE_LEFT)
				return MARIO_STATE_IDLE_LEFT;
			if (state == MARIO_STATE_IDLE_RIGHT)
				return MARIO_STATE_IDLE_RIGHT;
		}
	}
	return MARIO_STATE_AIR_LEFT;
	
}

 void PlayableCharacter::walk(int dir) {

	 if (dir == LEFT) {
		 this->_setState(MARIO_STATE_WALK_LEFT);
	 }
	 if (dir == RIGHT) {
		 this->_setState(MARIO_STATE_WALK_RIGHT);
	 }
 }
 void PlayableCharacter::run(int dir)
 {
	 if (dir == LEFT) {
		 this->_setState(MARIO_STATE_RUN_LEFT);
	 }
	 if (dir == RIGHT) {
		 this->_setState(MARIO_STATE_RUN_RIGHT);
	 }
	 //change property + change state for rendering
 }

 void PlayableCharacter::jump()
 {
	 //change property + change state for rendering
	 //checkground
	 this->_setState(MARIO_STATE_AIR);
	 //gravity;
	 //ay = -0.1f;
 }

 void PlayableCharacter::releaseJump()
 {
	 if (vy>7.0f )vy = 7.0f;
	 return;
 }

 void PlayableCharacter::slowDown()
 {
	 if (vx == 0.0f) { return; }
	 if (vx > 0) {
		 this->_setState(MARIO_STATE_IDLE_RIGHT);

	 }
	 else {
		 this->_setState(MARIO_STATE_IDLE_LEFT);
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
	 left = x - MARIO_WIDTH / 2;
	 right = x + MARIO_WIDTH;
	 top = y - MARIO_HEIGHT / 2;
	 bottom = y + MARIO_HEIGHT;

 }
 void PlayableCharacter::onCollisionWith(CollisionEvent* e)
 {

	 if (e->ny != 0 && e->des->isBlocking())
	 {
		 vy = 0;
		 if (e->ny < 0) isOnPlatform = true;
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
	 case MARIO_STATE_RUN_RIGHT:
		 //if (isSitting) break;
		 maxVx = MARIO_MAX_VELOCITY_RUN;
		 ax = MARIO_ACCELARATION_RUN;
		 //nx = 1;
		 break;
	 case MARIO_STATE_RUN_LEFT:
		 //if (isSitting) break;
		 maxVx = MARIO_MAX_VELOCITY_RUN;
		 ax = -MARIO_ACCELARATION_RUN;
		 //nx = -1;
		 break;
	 case MARIO_STATE_WALK_RIGHT:
		 //if (isSitting) break;
		 maxVx = MARIO_MAX_VELOCITY_WALK;
		 ax = MARIO_ACCELARATION_WALK;
		 //nx = 1;
		 break;
	 case MARIO_STATE_WALK_LEFT:
		 //if (isSitting) break;
		 maxVx = MARIO_MAX_VELOCITY_WALK;
		 ax = -MARIO_ACCELARATION_WALK;
		 //nx = -1;
		 break;
	 case MARIO_STATE_IDLE_LEFT:
	 case MARIO_STATE_IDLE_RIGHT:
		 ax = -0.0f;
		 vx = 0.0f;
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