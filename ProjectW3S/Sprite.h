#pragma once

#include <d3dx9.h>
#include <memory>
#include "Texture.h"
#include "Camera.h"

class Sprite {
public:
	Sprite(LPDIRECT3DDEVICE9 d3dDevice, TexturePtr texture, int pixelPerUnit)
		: m_d3dDevice(d3dDevice), m_tex(texture)
	{
		m_d3dDevice->CreateVertexBuffer(sizeof(SpriteVtx) * 4, D3DUSAGE_WRITEONLY, SpriteVtxFVF, D3DPOOL_MANAGED, &m_vtxBuf, NULL);

		setDiffuse(0xFFffFFff);
		setSize(static_cast<float>(m_tex->getSize().x)/pixelPerUnit, static_cast<float>(m_tex->getSize().y)/pixelPerUnit);
		setUV({ 0.0f, 0.0f, 1.0f, 1.0f });
		setVtx();

		D3DXMatrixIdentity(&m_world);
	}

	Sprite(LPDIRECT3DDEVICE9 d3dDevice, TexturePtr texture, float widht, float height)
		: m_d3dDevice(d3dDevice), m_tex(texture)
	{
		m_d3dDevice->CreateVertexBuffer(sizeof(SpriteVtx) * 4, D3DUSAGE_WRITEONLY, SpriteVtxFVF, D3DPOOL_MANAGED, &m_vtxBuf, NULL);
		setDiffuse(0xFFffFFff);
		setSize(widht, height);
		setUV({ 0.0f, 0.0f, 1.0f, 1.0f });
		setVtx();
		D3DXMatrixIdentity(&m_world);
	}

	~Sprite() {
		if (m_vtxBuf)
			m_vtxBuf->Release();
	}

	void draw(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, float scale = 1.0f) {
		D3DXMatrixIdentity(&m_world);
		setScale(scale, scale);
		setRot(rot.x, rot.y, rot.z);
		setPos(pos);
		m_d3dDevice->SetTransform(D3DTS_WORLD, &m_world);
		render();
	}

	void drawBillBoard(const D3DXVECTOR3& pos, CameraPtr camera, float scale = 1.0f) {
		D3DXMatrixIdentity(&m_world);
		setScale(scale, scale);
		lookCamera(camera);
		setPos(pos);
		m_d3dDevice->SetTransform(D3DTS_WORLD, &m_world);
		render();
	}

	void setDiffuse(const D3DCOLOR& diffuse) {
		for (int i = 0; i < 4; i++)
			m_vtx[i].diffuse = diffuse;
	}

	void setSize(float width, float height) {
		float w = width / 2;
		float h = height / 2;

		m_vtx[0].x = -w; m_vtx[0].y = h; m_vtx[0].z = 0;
		m_vtx[1].x = w; m_vtx[1].y = h; m_vtx[1].z = 0;
		m_vtx[2].x = -w; m_vtx[2].y = -h; m_vtx[2].z = 0;
		m_vtx[3].x = w; m_vtx[3].y = -h; m_vtx[3].z = 0;
	}

	void setUV(TextureUV uv) {
		m_vtx[0].u = uv.tu1; m_vtx[0].v = uv.tv1;
		m_vtx[1].u = uv.tu2; m_vtx[1].v = uv.tv1;
		m_vtx[2].u = uv.tu1; m_vtx[2].v = uv.tv2;
		m_vtx[3].u = uv.tu2; m_vtx[3].v = uv.tv2;
	}

	void setVtx() {
		SpriteVtx* data;
		if (SUCCEEDED(m_vtxBuf->Lock(0, 0, (void**)&data, 0))) {
			memcpy(data, m_vtx, sizeof(SpriteVtx)*4);
			m_vtxBuf->Unlock();
		}
	}
private:
	void render() {
		m_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_d3dDevice->SetTexture(0, m_tex->getTexPtr());
		m_d3dDevice->SetStreamSource(0, m_vtxBuf, 0, sizeof(SpriteVtx));
		m_d3dDevice->SetFVF(SpriteVtxFVF);
		m_d3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		m_d3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}

	void setScale(float x, float y) {
		D3DXMATRIX scale;
		D3DXMatrixScaling(&scale, x, y, 0);
		m_world *= scale;
	}

	void lookCamera(CameraPtr camera) {
		D3DXMATRIX view = camera->getViewMat();
		view._41 = view._42 = view._43 = 0;
		D3DXMatrixInverse(&view, NULL, &view);
		m_world *= view;
	}

	void setRot(float x, float y, float z) {
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, y, x, z);
		m_world *= rot;
	}

	void setPos(const D3DXVECTOR3& pos) {
		D3DXMATRIX trans;
		D3DXMatrixTranslation(&trans, pos.x, pos.y, pos.z);
		m_world *= trans;
	}

	struct SpriteVtx {
		float x, y, z;
		DWORD diffuse;
		float u, v;
	};
	static const WORD SpriteVtxFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	
	LPDIRECT3DDEVICE9 m_d3dDevice;
	TexturePtr m_tex;
	LPDIRECT3DVERTEXBUFFER9 m_vtxBuf;
	SpriteVtx m_vtx[4];
	D3DXMATRIX m_world;
};

using SpritePtr = std::shared_ptr<Sprite>;
