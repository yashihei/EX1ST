#pragma once

#include <d3dx9.h>
#include <string>
#include <vector>
#include <memory>
#include "Texture.h"

class Model {
public:
	Model(LPDIRECT3DDEVICE9 d3dDevice, std::string filePath) :
		m_d3dDevice(d3dDevice), m_mesh(), m_numMaterial()
	{
		//カレントディレクトリの取得(テクスチャのロードに必要)
		char dir_c[_MAX_DIR];
		_splitpath_s(TEXT(filePath.c_str()), NULL, 0, dir_c, _MAX_DIR, NULL, 0, NULL, 0);
		const std::string dir(dir_c);

		LPD3DXBUFFER mtrlBuf;
		HRESULT hr = D3DXLoadMeshFromX(TEXT(filePath.c_str()), D3DXMESH_SYSTEMMEM, m_d3dDevice, NULL, &mtrlBuf, NULL, &m_numMaterial, &m_mesh);
		if (FAILED(hr))
			throw std::runtime_error("Failed open" + filePath);

		D3DXMATERIAL* mtrlBufPtr = (D3DXMATERIAL*)mtrlBuf->GetBufferPointer();

		m_materials.resize(m_numMaterial);
		m_textures.resize(m_numMaterial, NULL);

		for (DWORD i = 0; i < m_numMaterial; i++) {
			m_materials[i] = mtrlBufPtr[i].MatD3D;
			if (mtrlBufPtr[i].pTextureFilename != NULL) {
				std::string texFilePath(dir);
				texFilePath += mtrlBufPtr[i].pTextureFilename;
				m_textures[i] = std::make_shared<Texture>(m_d3dDevice, texFilePath);
			}
		}

		mtrlBuf->Release();
	}

	~Model() {
		m_mesh->Release();
	}

	void draw(D3DXVECTOR3 pos, float yaw = 0.0f, float pitch = 0.0f, float roll = 0.0f, float ratio = 1.0f) {
		D3DXMATRIX world, trans, rot, scaling;
		D3DXMatrixTranslation(&trans, pos.x, pos.y, pos.z);
		D3DXMatrixRotationYawPitchRoll(&rot, yaw, pitch, roll);
		D3DXMatrixScaling(&scaling, ratio, ratio, ratio);

		D3DXMatrixIdentity(&world);
		D3DXMatrixMultiply(&world, &world, &scaling);
		D3DXMatrixMultiply(&world, &world, &rot);
		D3DXMatrixMultiply(&world, &world, &trans);

		draw(world);
	}

	void draw(D3DXMATRIX world) {
		m_d3dDevice->SetTransform(D3DTS_WORLD, &world);

		for (DWORD i = 0; i < m_numMaterial; i++) {
			if (m_textures[i] != NULL)
				m_d3dDevice->SetTexture(0, m_textures[i]->getTexPtr());
			else
				m_d3dDevice->SetTexture(0, NULL);
			m_d3dDevice->SetMaterial(&m_materials[i]);
			m_mesh->DrawSubset(i);
		}
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	LPD3DXMESH m_mesh;
	DWORD m_numMaterial;
	std::vector<TexturePtr> m_textures;
	std::vector<D3DMATERIAL9> m_materials;
};

using ModelPtr = std::shared_ptr<Model>;
