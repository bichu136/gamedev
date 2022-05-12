#include "AnimationManage.h"
#include <d3dx10.h>
#include "GlobalDefine.h"
AnimationManage* AnimationManage::__instance = NULL;
AnimationManage* AnimationManage::getInstance() {
	if (__instance == NULL) __instance = new AnimationManage();
	return __instance;
}
void AnimationManage::Add(int id, Animation* ani)
{
	animationList[id] = ani;
}
Animation* AnimationManage::Get(int id)
{
	return this->animationList[id];
}