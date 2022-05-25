#include "Plant.h"
#include "PlayableCharacter.h"
#include "GlobalDefine.h"
#include "QuestionBlock.h"
#include "WoodenFloor.h"
#include "LoadedResources.h"
#include "debug.h"
#define VELOCITY_X 3.1f
#define GRAVITY -2.0f
Plant::Plant(float x, float y) :GameObject(x, y)
{
	is_dead = false;
	dead_frame = 0;
	is_delete = false;
	isOnPlatform = false;
	vx = VELOCITY_X;
	vy = GRAVITY;
	origin_x = x;
	origin_y = y;
	is_collide = false;
	isOn = true;
	isOff = false;
	OnFrame += 1;
}


void Plant::Update(DWORD dt)
{
	LoadedResources* lr = LoadedResources::getInstance();
	//float x, y;
	//lr->Mario->GetPosition(x, y);
	if (isOn)
	{
		OnFrame = (OnFrame + 1) % 35;
		if (OnFrame!=0) {
			vx = 0;
			vy = 0;
		}
		else { 
			vx = VELOCITY_X;
			vy = GRAVITY;
			y += vy; 
			isOn = false; 
		}
		return;
	}
	if (isOff) {
		OffFrame = (OffFrame + 1) % 35;
		if (OffFrame!=0) {
			vx = 0;
			vy = 0;
		}
		else {
			vx = VELOCITY_X;
			vy = -GRAVITY;
			y += vy;
			isOff = false;
		}
		return;
	}
	//if not on or off
	if (y >= origin_y) {
		y = origin_y;
		isOn = true;
		vy = GRAVITY;
	}
	//if not on or off
	if (y <= (origin_y - BRICK_HEIGHT * 2 * SCALE_HEIGHT)) {
		y = (origin_y - BRICK_HEIGHT * 2 * SCALE_HEIGHT);
		isOff = true;
		vy = -GRAVITY;
	}
	setPositioned = false;
	//check collision
	DebugOutTitle(L"%0.5f,%0.5f", this->vx, this->vy);
	isOnPlatform = false;
	y += vy;
	//Collistion::getInstance->process(this);
}

int Plant::GetAnimationID(int i)
{
	return 0;
}

int Plant::getCorrectAnimation()
{
	return 4302;
}
void Plant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_WIDTH * SCALE_WIDTH / 2;
	top = y - BRICK_HEIGHT * SCALE_HEIGHT / 2;
	right = left + BRICK_WIDTH * SCALE_WIDTH;
	bottom = top + BRICK_HEIGHT * SCALE_HEIGHT;

}
void Plant::dead()
{
	is_dead = true;
}
void Plant::onCollisionWith(CollisionEvent* e, bool is_double_collision)
{
	//OnNoCollision();
	return;
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
		//return;
	}
	if (e->ny <= -1.0f && e->des->isBlockingBottom()) {
		y += e->t * vy + e->ny * 1.0f;
		//return;
	}
	if (e->nx == -1.0f && e->des->isBlockingLeft())
	{
		if (dynamic_cast<Pipe*>(e->des))
			dynamic_cast<Pipe*>(e->des);
		//DebugOutTitle(L"pipe collided %0.3f,%0.3f,%0.3f", this->x, this->y, this->vx);
	//return;
		if (is_collide) {
			is_collide = false;
		}
		else {
			vx = -vx;
			x += e->t * vx + e->nx * 1.0f;
			is_collide = false;
		}
		return;
	}
	if (e->nx == 1.0f && e->des->isBlockingRight())
	{
		if (is_collide) {
			is_collide = false;
		}
		else {
			vx = -vx;
			x += e->t * vx + e->nx * 1.0f;
			is_collide = false;

		}

		//return;
	}
	if (is_double_collision) { return; }
	OnNoCollision();
}
void Plant::OnNoCollision()
{
	y += vy;
}

void Plant::AddAnimation(int id)
{
	return;
}

