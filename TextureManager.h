#pragma once
#include <unordered_map>
#include <d3dx10.h>
#include "Texture.h"

class TextureManager
{
	private:
		static TextureManager* __instance;
		std::unordered_map<int,Texture*> TextureList;
	public:
		static TextureManager* getInstance();
		void Add(int id, LPCWSTR file_path);
		Texture* getTextureWithId(int id);


};

