#include "Box.h"
#include "GlobalDefine.h"
Box::Box(float x, float y, int width, int height, int box_color):WoodenFloor(x,y,width,height)
{
	switch(box_color) {
		case 1:
			sprite_1 = BOX_1_SPRITE_1;
			sprite_2 = BOX_1_SPRITE_2;
			sprite_3 = BOX_1_SPRITE_3;
			sprite_4 = BOX_1_SPRITE_4;
			sprite_5 = BOX_1_SPRITE_5;
			sprite_6 = BOX_1_SPRITE_6;
			sprite_7 = BOX_1_SPRITE_7;
			sprite_8 = BOX_1_SPRITE_8;
			sprite_9 = BOX_1_SPRITE_9;
			break;
		case 2:
			sprite_1 = BOX_2_SPRITE_1;
			sprite_2 = BOX_2_SPRITE_2;
			sprite_3 = BOX_2_SPRITE_3;
			sprite_4 = BOX_2_SPRITE_4;
			sprite_5 = BOX_2_SPRITE_5;
			sprite_6 = BOX_2_SPRITE_6;
			sprite_7 = BOX_2_SPRITE_7;
			sprite_8 = BOX_2_SPRITE_8;
			sprite_9 = BOX_2_SPRITE_9;
			break;
		case 3:
			sprite_1 = BOX_3_SPRITE_1;
			sprite_2 = BOX_3_SPRITE_2;
			sprite_3 = BOX_3_SPRITE_3;
			sprite_4 = BOX_3_SPRITE_4;
			sprite_5 = BOX_3_SPRITE_5;
			sprite_6 = BOX_3_SPRITE_6;
			sprite_7 = BOX_3_SPRITE_7;
			sprite_8 = BOX_3_SPRITE_8;
			sprite_9 = BOX_3_SPRITE_9;
			break;
		case 4:
			sprite_1 = BOX_4_SPRITE_1;
			sprite_2 = BOX_4_SPRITE_2;
			sprite_3 = BOX_4_SPRITE_3;
			sprite_4 = BOX_4_SPRITE_4;
			sprite_5 = BOX_4_SPRITE_5;
			sprite_6 = BOX_4_SPRITE_6;
			sprite_7 = BOX_4_SPRITE_7;
			sprite_8 = BOX_4_SPRITE_8;
			sprite_9 = BOX_4_SPRITE_9;
			break;
	}
}

int Box::getCorrectAnimationID()
{
	return 0;
}

int Box::GetAnimationID(int i)
{
	return 0;
}

void Box::AddAnimation(int id)
{
}

void Box::Update(DWORD dt)
{
}

int Box::getCorrectAnimation()
{
	return 0;
}

int Box::getCorrectSprite(int w_iter, int h_iter)
{
	if (w_iter == 0) {
		if (h_iter == 0) {
			return sprite_1;
		}
		else {
			if (h_iter == height - 1) {
				return sprite_7;
			}
			return sprite_4;

		}
	}
	else {
		if (w_iter == width - 1) {
			if (h_iter == 0) {
				return sprite_3;
			}
			else {
				if (h_iter == height - 1) {
					return sprite_9;
				}
				return sprite_6;
				
			}
		}
		else {
			if (h_iter == 0) {
				return sprite_2;
			}
			else {
				if (h_iter == height - 1) {
					return sprite_8;
				}
				return sprite_5;

			}
		}
	}
}

void Box::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_WIDTH * SCALE_WIDTH / 2;
	top = y - BRICK_HEIGHT * SCALE_HEIGHT / 2;
	bottom = top + BRICK_HEIGHT * height * SCALE_HEIGHT;
	right = left + BRICK_WIDTH * width * SCALE_WIDTH;
}
