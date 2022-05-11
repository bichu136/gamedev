#pragma once
#include"Texture.h"
class Sprite
{
private:
	int id;
	// the rectangular in which containing the sprite in the sprites sheets
	int left, top, right, bottom;
	DWORD StillFrame;
public:
	Texture* texture; // the texture array/sheets
	D3DX10_SPRITE sprite;
	D3DXMATRIX matrixScaling;
	Sprite(int id,
		   int left,
		   int top,
		   int right,
		   int bottom,
		   Texture* texture,
		   DWORD StillFrame = 1
	);
	DWORD getTime();
	void setTime(DWORD time);
	D3DX10_SPRITE* getD3dxSprite() { return &sprite; }
	D3DXMATRIX getMatrixScaling() { return matrixScaling; }
	void Draw(float x,float y);

};

