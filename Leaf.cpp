#include "Leaf.h"
#include "GlobalDefine.h"
#include "Debug.h"
#define VELOCITY_X 3.0f
#define GRAVITY -2.0f
#define SPAWN_TIME 60
Leaf::Leaf(float x, float y) :GameObject(x, y)
{
	is_spawning = true;
	spawn_frame = 0;
	is_delete = false;
	isOnPlatform = false;
	velocity_determine = 2;
	vx = VELOCITY_X;
	vy = GRAVITY;
}
void Leaf::Update(DWORD dt)
{
	if (is_spawning) {
		if (spawn_frame < SPAWN_TIME) {
			spawn_frame += 1;
			vy = 2.5f;
			vx = 0.0f;
			return;
		}
		else {
			is_spawning = false;
			vy = GRAVITY;
			//vx = VELOCITY_X;
		}

	}
	velocity_determine += 1;
	if (velocity_determine % 40 < 20) {
		vx = (velocity_determine%40+1)*0.2f * VELOCITY_X;
	}
	else {
		vx = -((velocity_determine%40+1)-20)*0.2f * VELOCITY_X;
	}
	if (abs(vx) >= 3.0f) {
		ax = -ax;
	}

	vy = GRAVITY;
	
	DebugOutTitle(L"%0.3f,%0.3f", this->x, this->y);
}

int Leaf::GetAnimationID(int i)
{
	return 0;
}

void Leaf::AddAnimation(int id)
{

}

int Leaf::getCorrectAnimation()
{
	return 4202;
}

void Leaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_WIDTH * SCALE_WIDTH / 2;
	top = y - BRICK_HEIGHT * SCALE_HEIGHT / 2;
	right = left + BRICK_WIDTH * SCALE_WIDTH;
	bottom = top + BRICK_HEIGHT * SCALE_HEIGHT;
}

void Leaf::dead()
{
}



void Leaf::onCollisionWith(CollisionEvent* e)
{
}

void Leaf::OnNoCollision()
{
	x += vx;
	y += vy;
}
