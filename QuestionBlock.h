#pragma once
#include "GameObject.h"
class QuestionBlock :
    public GameObject
{
	private:
		bool isActive;
		bool isDisable;
		int activeFrame;
	public:
		QuestionBlock(float x, float y);
		void active();
		void Update(DWORD dt);
		int GetAnimationID(int i);
		int getCorrectAnimation();
		void AddAnimation(int id);
		void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

