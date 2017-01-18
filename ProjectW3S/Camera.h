#pragma once

#include <d3dx9.h>
#include <memory>

class Camera {
public:
	Camera(LPDIRECT3DDEVICE9 d3dDevice, D3DXVECTOR3 pos, D3DXVECTOR3 lookAt) :
		m_d3dDevice(d3dDevice), m_pos(pos), m_lookAt(lookAt), m_up(0.0f, 1.0f, 0.0f)
	{
		D3DVIEWPORT9 vp;
		m_d3dDevice->GetViewport(&vp);
		const float aspect = (float)vp.Width / (float)vp.Height;
		setAspect(aspect);
		reflect();
	}

	void setAspect(float aspect) {
		D3DXMATRIX proj;
		D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(45.0f), aspect, 1.0f, 1000.0f);
		m_d3dDevice->SetTransform(D3DTS_PROJECTION, &proj);
	}

	void moveTo(D3DXVECTOR3 pos) {
		m_pos = pos;
		reflect();
	}

	void lookAt(D3DXVECTOR3 pos) {
		m_lookAt = pos;
		reflect();
	}

	D3DXMATRIX getViewMat() const { return m_view; }
	D3DXVECTOR3 getPos() const { return m_pos; }
private:
	void reflect() {
		D3DXMatrixLookAtLH(&m_view, &m_pos, &m_lookAt, &m_up);
		m_d3dDevice->SetTransform(D3DTS_VIEW, &m_view);
	}

	LPDIRECT3DDEVICE9 m_d3dDevice;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_lookAt;
	D3DXVECTOR3 m_up;
	D3DXMATRIX m_view;
};

using CameraPtr = std::shared_ptr<Camera>;
