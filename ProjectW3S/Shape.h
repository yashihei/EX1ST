#pragma once

#include <d3dx9.h>
#include <memory>
#include <vector>

class Shape {
public:
	Shape(LPDIRECT3DDEVICE9 d3dDevice) :
		m_d3dDevice(d3dDevice)
	{
		D3DXCreateMeshFVF(2, 4, D3DXMESH_MANAGED, D3DFVF_XYZ, d3dDevice, &m_mesh);

		ShapeVertex* vtxBuf;
		m_mesh->LockVertexBuffer(0, (void**)&vtxBuf);
		vtxBuf[0].pos = D3DXVECTOR3(-1.0f, +1.0f, 0);
		vtxBuf[1].pos = D3DXVECTOR3(+1.0f, +1.0f, 0);
		vtxBuf[2].pos = D3DXVECTOR3(-1.0f, -1.0f, 0);
		vtxBuf[3].pos = D3DXVECTOR3(+1.0f, -1.0f, 0);
		m_mesh->UnlockVertexBuffer();

		WORD* idxBuf;
		m_mesh->LockIndexBuffer(0, (void**)&idxBuf);
		idxBuf[0] = 0;
		idxBuf[1] = 1;
		idxBuf[2] = 2;
		idxBuf[3] = 1;
		idxBuf[4] = 3;
		idxBuf[5] = 2;
		m_mesh->UnlockIndexBuffer();

		DWORD* subset;
		m_mesh->LockAttributeBuffer(0, &subset);
		subset[0] = 0;
		subset[1] = 0;
		m_mesh->UnlockAttributeBuffer();

		m_material = D3DMATERIAL9{ {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, 0 };
	}
	void draw(D3DXMATRIX world) {
		m_d3dDevice->SetTransform(D3DTS_WORLD, &world);
		m_d3dDevice->SetMaterial(&m_material);
		m_mesh->DrawSubset(0);
	}
private:
	struct ShapeVertex {
		D3DXVECTOR3 pos;
	};
	LPDIRECT3DDEVICE9 m_d3dDevice;
	LPD3DXMESH m_mesh;
	D3DMATERIAL9 m_material;
};

using ShapePtr = std::shared_ptr<Shape>;
