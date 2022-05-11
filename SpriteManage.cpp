#include "SpriteManage.h"
#include <d3dx10.h>
#include "GlobalDefine.h"
SpriteManage* SpriteManage::__instance = NULL;
SpriteManage* SpriteManage::getInstance() {
	if (__instance == NULL) __instance = new SpriteManage();
	return __instance;
}

void SpriteManage::Add(int id, int left, int top, int right, int bottom, Texture* texture,DWORD StillFrame)
{
	Sprite* s = new Sprite(id, left, top, right, bottom, texture);
	s->setTime(StillFrame);
	spriteList[id] = s;
}
