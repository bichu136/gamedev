#include "WoodenFloor.h"
#include"GlobalDefine.h"
WoodenFloor::WoodenFloor(float x, float y, int width, int height):GameObject(x,y)
{
	sprite_1 = WOODEN_FLOOR_SPRITE_1;
	sprite_2 = WOODEN_FLOOR_SPRITE_2;
	sprite_3 = WOODEN_FLOOR_SPRITE_3;
	sprite_4 = WOODEN_FLOOR_SPRITE_4;
	sprite_5 = WOODEN_FLOOR_SPRITE_5;
	sprite_6 = WOODEN_FLOOR_SPRITE_6;
	sprite_7 = WOODEN_FLOOR_SPRITE_7;
	sprite_8 = WOODEN_FLOOR_SPRITE_8;
	sprite_9 = WOODEN_FLOOR_SPRITE_9;
	this->width = width;
	this -> height = height;
}

void WoodenFloor::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_WIDTH * SCALE_WIDTH / 2;
	top = y- BRICK_HEIGHT * SCALE_HEIGHT / 2;
	bottom = top + BRICK_WIDTH * height * SCALE_WIDTH;
	right = left + BRICK_WIDTH * width * SCALE_WIDTH;
	
	
}

int WoodenFloor::getCorrectSprite(int w_iter, int h_iter)
{
	if (h_iter == (height - 1))
	{
		if (w_iter == 0) {
			return sprite_7;
		}
		else if (w_iter == (width - 1)) {
			return sprite_9;
		}
		else {
			return sprite_8;
		}
	}
	else {
		if (w_iter == 0) {
			return sprite_4;
		}
		else if (w_iter == (width - 1)) {
			return sprite_6;
		}
		else {
			return sprite_5;
		}
	}
}

void WoodenFloor::getCorrectSpritePosition(int w_iter, int h_iter, float& x, float& y)
{
	x = this->x + w_iter * BRICK_WIDTH * SCALE_WIDTH;
	y = this->y + h_iter*BRICK_HEIGHT*SCALE_HEIGHT;
}
