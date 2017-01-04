#pragma once

#include <d3dx9.h>
#include <memory>
#include <vector>

class Shape {
public:
	Shape(LPDIRECT3DDEVICE9 d3dDevice) :
		m_d3dDevice(d3dDevice)
	{}
	void draw(D3DXMATRIX world) {
		m_d3dDevice->SetTransform(D3DTS_WORLD, &world);
		m_d3dDevice->SetMaterial(&m_material);
		m_mesh->DrawSubset(0);
	}

	void addVertex(float x, float y, float z) {
		ShapeVertex sv;
		sv.x = x, sv.y = y, sv.z = z;
		m_vertices.push_back(sv);
	}

	void setVertexBuffer() {
		ShapeVertex* vtxBuf;
		m_mesh->LockVertexBuffer(0, (void**)&vtxBuf);
		memcpy(vtxBuf, m_vertices.data(), m_vertices.size() * sizeof(ShapeVertex));
		m_mesh->UnlockVertexBuffer();
	}
	void setIndexBuffer() {
		WORD* idxBuf;
		m_mesh->LockIndexBuffer(0, (void**)&idxBuf);
		memcpy(idxBuf, m_indices.data(), m_indices.size() * sizeof(WORD));
		m_mesh->UnlockIndexBuffer();
	}
	void setAttributeBuffer() {
		DWORD* attributeBuf;
		m_mesh->LockAttributeBuffer(0, &attributeBuf);
		memcpy(attributeBuf, m_attributes.data(), m_attributes.size() * sizeof(DWORD));
		m_mesh->UnlockAttributeBuffer();
	}
protected:
	struct ShapeVertex {
		float x, y, z;
	};
	LPDIRECT3DDEVICE9 m_d3dDevice;
	LPD3DXMESH m_mesh;
	D3DMATERIAL9 m_material;

	std::vector<ShapeVertex> m_vertices;
	std::vector<WORD> m_indices;
	std::vector<DWORD> m_attributes;
};

using ShapePtr = std::shared_ptr<Shape>;

class Box : public Shape {
public:
	Box(LPDIRECT3DDEVICE9 d3dDevice) :
		Shape(d3dDevice)
	{
		D3DXCreateMeshFVF(2, 4, D3DXMESH_MANAGED, D3DFVF_XYZ, d3dDevice, &m_mesh);

		addVertex(-1.0f, 1.0f, 0);
		addVertex(1.0f, 1.0f, 0);
		addVertex(-1.0f, -1.0f, 0);
		addVertex(1.0f, -1.0f, 0);
		setVertexBuffer();

		WORD quadIndices[] = { 0, 1, 2, 1, 3, 2 };
		for (WORD index : quadIndices) {
			m_indices.push_back(index);
		}
		setIndexBuffer();

		for (int i = 0; i < m_indices.size() / 3; i++) {
			m_attributes.push_back(0);
		}
		setAttributeBuffer();

		m_material = D3DMATERIAL9{ {1, 0, 0, 1}, {1, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, 0 };
	}
};
