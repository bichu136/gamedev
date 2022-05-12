#include "Animation.h"
#include "SpriteManage.h"
#include "GlobalDefine.h"
void Animation::Add(int spriteID, DWORD time)
{
	spriteIDList.push_back(spriteID);
	timeforSpriteList.push_back(time);
}
void Animation::Add(int spriteID)
{
	spriteIDList.push_back(spriteID);
	timeforSpriteList.push_back(0);
}

int Animation::getCorrectSpriteID()
{
	SpriteManage* sm = SpriteManage::getInstance();
	ULONGLONG now = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;
	if (currentFrame < 0) {
		currentFrame = 0;
		lastFrameTime = now;
	}
	else {
		
		
		DWORD t = timeforSpriteList[currentFrame];

		if (now - lastFrameTime > t*tickPerFrame) {
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == spriteIDList.size()) currentFrame = 0;
		}
		
	}
	return spriteIDList[currentFrame];
}
