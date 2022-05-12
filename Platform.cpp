#include "Platform.h"
#include "Globaldefine.h"
Platform::Platform(float x, float y) :GameObject(x, y)
{	
}

void Platform::Update(DWORD dt)
{
}

int Platform::GetAnimationID(int i)
{
	return this->animationIDList[i];
}
int Platform::getCorrectAnimation() {
		return this->animationIDList[0];
}

void Platform::AddAnimation(int id)
{
	animationIDList.push_back(id);
}

void Platform::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_WIDTH*SCALE_WIDTH / 2;
	top = y - BRICK_HEIGHT*SCALE_HEIGHT / 2;
	right = left + BRICK_WIDTH * SCALE_WIDTH;
	bottom = top + BRICK_HEIGHT * SCALE_HEIGHT;
}
