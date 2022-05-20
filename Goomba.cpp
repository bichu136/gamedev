#include "Goomba.h"
#include "PlayableCharacter.h"
#include "GlobalDefine.h"
#include "QuestionBlock.h"
#include "WoodenFloor.h"
#include "debug.h"
#define VELOCITY_X 3.0f
#define GRAVITY -2.0f
Goomba::Goomba(float x, float y) :GameObject(x, y)
{
	is_dead = false;
	dead_frame = 0;
	is_delete = false;
	isOnPlatform = false;
	vx = VELOCITY_X;
	vy = GRAVITY;
}


void Goomba::Update(DWORD dt)
{
	if (is_dead) {
		dead_frame += 1;
		if (dead_frame % 8 == 0) {
			is_delete = true;
		}
	}
	setPositioned = false;
	//check collision
	//DebugOutTitle(L"%0.3f,%0.3f", this->x, this->y);
	isOnPlatform = false;

	//Collistion::getInstance->process(this);
}

int Goomba::GetAnimationID(int i)
{
	return 0;
}

int Goomba::getCorrectAnimation()
{
	//return SMALL_MARIO_STATE_IDLE_LEFT;
	if (is_dead) {
		return 4009;
	}
	else {
		return 4001;
	}
}
void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_WIDTH * SCALE_WIDTH / 2;
	top = y - BRICK_HEIGHT * SCALE_HEIGHT / 2;
	right = left + BRICK_WIDTH * SCALE_WIDTH;
	bottom = top + BRICK_HEIGHT * SCALE_HEIGHT;

}
void Goomba::dead()
{
	is_dead = true;
}
void Goomba::onCollisionWith(CollisionEvent* e,bool is_double_collision)
{
	if (e->ny >= 1.0f && e->des->isBlockingTop())
	{
		y += e->t * vy + e->ny * 1.0f;
		float block_left, block_top, block_right, block_bottom;
		float this_left, this_top, this_right, this_bottom;
		e->des->GetBoundingBox(block_left, block_top, block_right, block_bottom);
		this->GetBoundingBox(this_left, this_top, this_right, this_bottom);
		//DebugOutTitle(L"%0.3f,%0.3f,%0.3f", this->x, this->y, this->vx);
		/*if (block_left >= this_left || block_right <= this_right) {
			vx = -vx;
			x += vx * 1.5f;
		}*/
		vy = 0.0f;
		//OnNoCollision();
		return;
	}
	if (e->ny <= -1.0f && e->des->isBlockingBottom()) {
		y += e->t * vy + e->ny * 1.0f;
		return;
	}
	if (e->nx != 0 && e->des->isBlockingLeft())
	{
		x += e->t * vx + e->nx * 1.0f;
		vx = -vx;
		return;
	}
	if (e->nx != 0 && e->des->isBlockingRight())
	{
		x += e->t * vx + e->nx * 1.0f;
		vx = -vx;
		return;
	}
	if (is_double_collision) { return; }
	OnNoCollision();
}
void Goomba::OnNoCollision()
{
	x += vx;
	y += vy;
}

void Goomba::AddAnimation(int id)
{
	return;
}

