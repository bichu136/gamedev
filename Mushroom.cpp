#include "Mushroom.h"
#include "GlobalDefine.h"
#include "Debug.h"
#define VELOCITY_X 3.0f
#define GRAVITY -2.0f
#define SPAWN_TIME 60
Mushroom::Mushroom(float x, float y) :GameObject(x, y)
{
	is_spawning = true;
	spawn_frame = 0;
	is_delete = false;
	isOnPlatform = false;
	vx = VELOCITY_X;
	vy = GRAVITY;
}
void Mushroom::Update(DWORD dt)
{
	if (is_spawning) {
		if (spawn_frame < SPAWN_TIME) {
			spawn_frame += 1;
			vy = 1.0f;
			vx = 0.0f;
			return;
		}
		else {
			is_spawning = false;
			vy = GRAVITY;
			vx = VELOCITY_X;
		}
		
	}
	vy = GRAVITY;
	//DebugOutTitle(L"%0.3f,%0.3f", this->x, this->y);
}

int Mushroom::GetAnimationID(int i)
{
	return 0;
}

void Mushroom::AddAnimation(int id)
{

}

int Mushroom::getCorrectAnimation()
{
	return 4201;
}

void Mushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_WIDTH * SCALE_WIDTH / 2;
	top = y - BRICK_HEIGHT * SCALE_HEIGHT / 2;
	right = left + BRICK_WIDTH * SCALE_WIDTH;
	bottom = top + BRICK_HEIGHT * SCALE_HEIGHT;
}

void Mushroom::dead()
{
}

void Mushroom::onCollisionWith(CollisionEvent* e, bool is_double_collision)
{
	if (e->ny >= 1.0f && e->des->isBlockingTop())
	{
		y += e->t * vy + e->ny * 1.0f;
		float block_left, block_top, block_right, block_bottom;
		float this_left, this_top, this_right, this_bottom;
		e->des->GetBoundingBox(block_left, block_top, block_right, block_bottom);
		this->GetBoundingBox(this_left, this_top, this_right, this_bottom);
		
		/*if (block_left >= this_left || block_right <= this_right) {
			vx = -vx;
			x += vx * 1.5f;
		}*/
		vy = 0.0f;
		//OnNoCollision();
		//return;
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

void Mushroom::onCollisionWith(CollisionEvent* e)
{
}

void Mushroom::OnNoCollision()
{
	x += vx;
	y += vy;
}
