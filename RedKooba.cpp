#include "RedKooba.h"
#include "PlayableCharacter.h"
#include "GlobalDefine.h"
#include "QuestionBlock.h"
#include "WoodenFloor.h"
#include "Box.h"
#include "debug.h"
#define VELOCITY_X -3.0f
#define VELOCITY_ROLL -7.0f
#define GRAVITY -2.0f
#define WALK 0
#define ROLL 2
#define SHELL 1
RedKooba::RedKooba(float x, float y) :GameObject(x, y)
{
	is_dead = false;
	dead_frame = 0;
	is_delete = false;
	isOnPlatform = false;
	not_fall = true;
	vx = VELOCITY_X;
	vy = GRAVITY;
	state = WALK;
}


void RedKooba::Update(DWORD dt)
{

	vy = GRAVITY;
	setPositioned = false;
	//check collision
	//DebugOutTitle(L"%0.3f,%0.3f", this->x, this->y);
	isOnPlatform = false;

	//Collistion::getInstance->process(this);
}

int RedKooba::GetAnimationID(int i)
{
	return 0;
}

int RedKooba::getCorrectAnimation()
{
	//return SMALL_MARIO_STATE_IDLE_LEFT;
	switch (state) {
	case ROLL:
	case SHELL:
		return 4109;
	case WALK:
		return 4101;
	}
}
void RedKooba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_WIDTH * SCALE_WIDTH / 2+16.0f;
	top = y - BRICK_HEIGHT * SCALE_HEIGHT / 2 +16.0f;
	right = left + BRICK_WIDTH * SCALE_WIDTH -20.0f;
	bottom = top + BRICK_HEIGHT * SCALE_HEIGHT + 16.0f;

}
void RedKooba::dead()
{
	//is_dead = true;
	switch (state) {
	case WALK:
		state = SHELL;
		vx = 0;
		vy = GRAVITY;
		break;
	case ROLL:
		state = SHELL;
		vx = 0;
		vy = GRAVITY;
		break;
	case SHELL:
		not_fall = false;
		vx = VELOCITY_ROLL;
		vy = GRAVITY;
		break;

	}


	
}
void RedKooba::onCollisionWith(CollisionEvent* e,bool is_double_collision)
{
	//if (dynamic_cast<QuestionBlock*>(e->des)) {
	//	QuestionBlock* interact_with = dynamic_cast<QuestionBlock*>(e->des);
	//	if (e->ny >= 1.0f) {
	//			
	//	return;
	//}
	//if (e->ny == 0 &&e->nx ==0){
	//	this->x = this->x;
	//}
	if (!isCollidable()) return;
	if (e->ny == 1.0f && e->des->isBlockingTop())
	{
		y += e->t * vy + e->ny * 1.0f;
		if (setPositioned) {
			x -= vx*1.5f;
			y -= vy*1.5f;
		}
		float block_left, block_top, block_right, block_bottom;
		float this_left, this_top, this_right, this_bottom;
		e->des->GetBoundingBox(block_left, block_top, block_right, block_bottom);
		this->GetBoundingBox(this_left, this_top, this_right, this_bottom);
		//DebugOutTitle(L"%0.3f,%0.3f,%0.3f", this->x, this->y, this->vx);
		if (not_fall){
			if (block_left >= this_left || block_right <= this_right) {
				vx = -vx;
				x += vx * 1.5f;
			}
		}
		
		vy = 0.0f;
		
		//OnNoCollision();
	}
	if (e->ny == -1.0f && e->des->isBlockingBottom()) {
		y += e->t * vy + e->ny * 1.0f;
		return;
	}
	if (e->nx == -1.0f  && e->des->isBlockingLeft())
	{
		x += e->t * vx + e->nx * 1.0f;
		vx = -vx;
		if (state == ROLL) {
			if (dynamic_cast<QuestionBlock*>(e->des)) {
				dynamic_cast<QuestionBlock*>(e->des)->active();
			}
		}
		return;
	}
	if (e->nx == 1.0f && e->des->isBlockingRight())
	{
		x += e->t * vx + e->nx * 1.0f;
		vx = -vx;
		if (state == ROLL) {
			if (dynamic_cast<QuestionBlock*>(e->des)) {
				dynamic_cast<QuestionBlock*>(e->des)->active();
			}
		}
		return;
	}
	if (is_double_collision) { return; }
	
	OnNoCollision();
}
void RedKooba::OnNoCollision()
{
	setPositioned = true;
	x += vx;
	y += vy;
}

void RedKooba::AddAnimation(int id)
{
	return;
}

