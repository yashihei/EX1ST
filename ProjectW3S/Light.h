#pragma once

#include <d3dx9.h>
#include <memory>

class Light {
public:
	Light(LPDIRECT3DDEVICE9 d3dDevice, D3DXVECTOR3 dir, D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular) :
		m_d3dDevice(d3dDevice), m_light(), m_index(0)
	{
		m_light.Type = D3DLIGHT_DIRECTIONAL;
		setColor(diffuse, ambient, specular);
		setDir(dir);
		reflect(true);

		m_d3dDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
		m_d3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	void setPos(D3DXVECTOR3 pos) {
		m_light.Position = pos;
	}

	void setDir(D3DXVECTOR3 dir) {
		D3DXVec3Normalize((D3DXVECTOR3*)&m_light.Direction, &dir);
	}

	void setColor(D3DCOLORVALUE diffuse, D3DCOLORVALUE ambient, D3DCOLORVALUE specular) {
		m_light.Diffuse = diffuse;
		m_light.Ambient = ambient;
		m_light.Specular = specular;
	}

	void reflect(bool enable) {
		if (enable) {
			m_d3dDevice->SetLight(m_index, &m_light);
			m_d3dDevice->LightEnable(m_index, TRUE);
		} else {
			m_d3dDevice->LightEnable(m_index, FALSE);
		}
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	D3DLIGHT9 m_light;
	int m_index;
};

using LightPtr = std::shared_ptr<Light>;
