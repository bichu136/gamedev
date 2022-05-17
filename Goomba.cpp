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
void Goomba::onCollisionWith(CollisionEvent* e)
{

	if (e->ny != 0 && e->des->isBlocking())
	{
		vy = 0;
		isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->des->isBlocking())
		{
			vx = -vx;
		}
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

