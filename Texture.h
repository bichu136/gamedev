#pragma once
#include <d3d10.h>
#include <d3dx10.h>
class Texture
{
	protected:
		ID3D10Texture2D *_texture;
		ID3D10ShaderResourceView* _resourceView;
		int _height;
		int _width;
	public:
		Texture();
		Texture(ID3D10Texture2D* _texture, ID3D10ShaderResourceView* _resourceView)
		{
			this->_texture = _texture;
			this->_resourceView = _resourceView;

			D3D10_TEXTURE2D_DESC desc;
			this->_texture->GetDesc(&desc);
			this->_width = desc.Width;
			this->_height = desc.Height;
		}
		~Texture();
		ID3D10ShaderResourceView* getShaderResourceView() { return this->_resourceView; }
		int getHeight() { return this->_height; }
		int getWidth() { return this->_width; }
};

typedef  Texture * LPTEXTURE;
