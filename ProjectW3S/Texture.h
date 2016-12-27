#pragma once

#include <d3dx9.h>
#include <string>
#include <memory>
#include "Point.h"

class Texture {
public:
	Texture(LPDIRECT3DDEVICE9 d3dDevice, std::string filePath) :
		m_d3dDevice(d3dDevice), m_tex(), m_size(0, 0)
	{
		HRESULT hr = D3DXCreateTextureFromFile(m_d3dDevice, TEXT(filePath.c_str()), &m_tex);
		if (FAILED(hr))
			throw std::runtime_error("Failed load " + filePath);

		//‰æ‘œ‚ÌƒTƒCƒY‚ðŽæ“¾
		D3DXIMAGE_INFO info;
		D3DXGetImageInfoFromFile(filePath.c_str(), &info);
		m_size.x = info.Width;
		m_size.y = info.Height;
	}

	~Texture() {
		if (m_tex) m_tex->Release();
	}

	LPDIRECT3DTEXTURE9 getTexPtr() const { return m_tex; }
	Point getSize() const { return m_size; }
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	LPDIRECT3DTEXTURE9 m_tex;
	Point m_size;
};

using TexturePtr = std::shared_ptr<Texture>;
