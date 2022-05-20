#include "SpriteManage.h"
#include <d3dx10.h>
#include "GlobalDefine.h"
SpriteManage* SpriteManage::__instance = NULL;
SpriteManage* SpriteManage::getInstance() {
	if (__instance == NULL) __instance = new SpriteManage();
	return __instance;
}

void SpriteManage::Add(int id, int left, int top, int right, int bottom, Texture* texture, float offset_x ,float offset_y , DWORD StillFrame)
{
	Sprite* s = new Sprite(id, left, top, right, bottom, texture);
	s->setTime(StillFrame);
	s->offset_x = offset_x;
	s->offset_y = offset_y;
	spriteList[id] = s;
}
