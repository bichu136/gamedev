#include "Sprite.h"
#include "GlobalDefine.h"
Sprite::Sprite(int id, int left, int top, int right, int bottom, Texture* texture, DWORD StillFrame)
{
	this->id = id;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->texture = texture;
	this->offset_x = 0;
	this->offset_y = 0;
	// get sprite from texture(spites sheets) and create a matrixScaling;
	sprite.pTexture = texture->getShaderResourceView();
	sprite.TexCoord.x = this->left / (float)texture->getWidth();
	sprite.TexCoord.y = this->top / (float)texture->getHeight();
	this->StillFrame = StillFrame;
	
	int spriteWidth = (this->right - this->left + 1);
	int spriteHeight = (this->bottom - this->top + 1);

	//shrink size in order to fix [0,1]
	sprite.TexSize.x = spriteWidth / (float)texture->getWidth();
	sprite.TexSize.y = spriteHeight / (float)texture->getHeight();
	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;
	D3DXMatrixScaling(&matrixScaling, (float)spriteWidth*SCALE_WIDTH, (float)spriteHeight*SCALE_HEIGHT, -1.0f);

}

DWORD Sprite::getTime()
{
	return this->StillFrame;
}

void Sprite::setTime(DWORD time)
{
	this->StillFrame = time;
}

