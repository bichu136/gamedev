#pragma once
#include <unordered_map>

#include <d3dx10.h>

#include "Texture.h"
#include "Sprite.h"
class SpriteManage
{	
	private:
		static SpriteManage *__instance;
		std::unordered_map<int, Sprite*> spriteList;
		
	public:
		static SpriteManage* getInstance();
		Sprite* Get(int id) { return spriteList[id]; };
		void Add(int id,
			     int left,
			     int top,
			     int right,
			     int bottom,
			     Texture* texture,
				 float offset_x =0,
				 float offset_y = 0,
			     DWORD StillFrame =1
		);


};

