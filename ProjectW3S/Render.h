#pragma once

#include <d3dx9.h>

inline void EnebleNormalBlend(LPDIRECT3DDEVICE9 d3dDevice) {
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

inline void EnebleAddBlend(LPDIRECT3DDEVICE9 d3dDevice) {
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

inline void EnebleSubBlend(LPDIRECT3DDEVICE9 d3dDevice) {
	d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_SRCALPHA);
	d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR);
}

inline void DisableZBuf(LPDIRECT3DDEVICE9 d3dDevice) {
	d3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
}

inline void EnebleZBuf(LPDIRECT3DDEVICE9 d3dDevice) {
	d3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}
