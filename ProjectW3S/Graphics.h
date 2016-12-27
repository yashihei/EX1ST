#pragma once

#include <d3dx9.h>
#include <memory>

#pragma comment(lib, "d3d9.lib")
#if defined(DEBUG) || defined(_DEBUG)
	#pragma comment(lib, "d3dx9d.lib")
#else
	#pragma comment(lib, "d3dx9.lib")
#endif
#pragma comment(lib, "dxguid.lib")

class Graphics {
public:
	Graphics(HWND hWnd, bool fullScreen);
	~Graphics();

	HRESULT beginScene(int r, int g, int b);
	HRESULT endScene();
	HRESULT present();
	LPDIRECT3DDEVICE9 getDevice() { return m_d3dDevice; }
private:
	LPDIRECT3D9 m_d3d;
	LPDIRECT3DDEVICE9 m_d3dDevice;
};

using GraphicsPtr = std::shared_ptr<Graphics>;
