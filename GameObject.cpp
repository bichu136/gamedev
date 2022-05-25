#include "GameObject.h"

//void GameObject::onCollisionWith(CollisionEvent* e, bool is_double_collision)
//{
//	if (e->ny >= 1.0f && e->des->isBlockingTop())
//	{
//		y += e->t * vy + e->ny * 1.0f;
//		float block_left, block_top, block_right, block_bottom;
//		float this_left, this_top, this_right, this_bottom;
//		e->des->GetBoundingBox(block_left, block_top, block_right, block_bottom);
//		this->GetBoundingBox(this_left, this_top, this_right, this_bottom);
//
//		/*if (block_left >= this_left || block_right <= this_right) {
//			vx = -vx;
//			x += vx * 1.5f;
//		}*/
//		vy = 0.0f;
//		//OnNoCollision();
//		//return;
//	}
//	if (e->ny <= -1.0f && e->des->isBlockingBottom()) {
//		y += e->t * vy + e->ny * 1.0f;
//		return;
//	}
//	if (e->nx != 0 && e->des->isBlockingLeft())
//	{
//		x += e->t * vx + e->nx * 1.0f;
//		vx = -vx;
//		return;
//	}
//	if (e->nx != 0 && e->des->isBlockingRight())
//	{
//		x += e->t * vx + e->nx * 1.0f;
//		vx = -vx;
//		return;
//	}
//	if (is_double_collision) { return; }
//	OnNoCollision();
//}
