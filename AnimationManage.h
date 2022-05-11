#pragma once
#include"Animation.h"
#include<unordered_map>
class AnimationManage
{
	private:
		static AnimationManage* __instance;
		std::unordered_map<int, Animation*> animationList;
	public:
		static AnimationManage* getInstance();
		//AnimationManage();
		void Add(int id, Animation* ani);
		Animation* Get(int id);
};