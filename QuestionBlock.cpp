#include "QuestionBlock.h"
#include "Globaldefine.h"
#include "LoadedResources.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "debug.h"
QuestionBlock::QuestionBlock(float x, float y,bool havePowerUp) :GameObject(x, y)
{
	this->drawAtFront = true;
	isActive = false;
	isDisable = false;
	this->havePowerUp = havePowerUp;
	activeFrame = 0;
}

void QuestionBlock::Update(DWORD dt)
{
	if (isActive){
		//DebugOutTitle(L"nx: %0.5f,ny: %0.5f");
		activeFrame += 1;
		if (activeFrame % 13 == 0) {
			isActive = false;
			isDisable = true;				
		}
		else {
			if (activeFrame > 6)
				y -= 3.0f;
			else
				y += 3.0f;
		}
	}
}

int QuestionBlock::GetAnimationID(int i)
{
	return this->animationIDList[i];
}
int QuestionBlock::getCorrectAnimation() {
	if (isDisable) {
		return 3099;
	}
	else {
		return 3001;
	}
	
}
void QuestionBlock::active() {
	if (isDisable) {
		return;
	}
	else {
		isActive = true;
		if (havePowerUp) {
			LoadedResources* lr = LoadedResources::getInstance();
			if (lr->Mario->powerUpLevel == BIG) {
				// spawn tanuki leaf;
				lr->enemies.push_back(new Leaf(this->x, this->y));
			}
			if (lr->Mario->powerUpLevel == SMALL) {
				//spawn mushroom
				lr->enemies.push_back(new Mushroom(this->x, this->y));
			}
		}
		else {
			//spawn coins
		}
	}
}
void QuestionBlock::AddAnimation(int id)
{
	animationIDList.push_back(id);
}

void QuestionBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BRICK_WIDTH * SCALE_WIDTH / 2;
	top = y - BRICK_HEIGHT * SCALE_HEIGHT / 2;
	right = left + BRICK_WIDTH * SCALE_WIDTH;
	bottom = top + BRICK_HEIGHT * SCALE_HEIGHT;
}
