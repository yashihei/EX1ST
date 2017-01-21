#pragma once

#include <d3dx9.h>
#include <string>
#include <vector>
#include <memory>
#include "Texture.h"

class XModel {
public:
	XModel(LPDIRECT3DDEVICE9 d3dDevice, const std::string& filePath) :
		m_d3dDevice(d3dDevice), m_mesh(), m_numMaterial()
	{
		//カレントディレクトリの取得(テクスチャのロードに必要)
		char dir_c[_MAX_DIR];
		_splitpath_s(TEXT(filePath.c_str()), NULL, 0, dir_c, _MAX_DIR, NULL, 0, NULL, 0);
		const std::string dir(dir_c);

		LPD3DXBUFFER mtrlBuf;
		HRESULT hr = D3DXLoadMeshFromX(TEXT(filePath.c_str()), D3DXMESH_SYSTEMMEM, m_d3dDevice, NULL, &mtrlBuf, NULL, &m_numMaterial, &m_mesh);
		if (FAILED(hr))
			throw std::runtime_error("Failed load " + filePath);

		D3DXMATERIAL* mtrlBufPtr = (D3DXMATERIAL*)mtrlBuf->GetBufferPointer();

		m_materials.resize(m_numMaterial);
		m_textures.resize(m_numMaterial, NULL);

		for (DWORD i = 0; i < m_numMaterial; i++) {
			m_materials[i] = mtrlBufPtr[i].MatD3D;
			m_materials[i].Ambient = m_materials[i].Diffuse;
			if (mtrlBufPtr[i].pTextureFilename != NULL) {
				std::string texFilePath(dir);
				texFilePath += mtrlBufPtr[i].pTextureFilename;
				m_textures[i] = std::make_shared<Texture>(m_d3dDevice, texFilePath);
			}
		}

		mtrlBuf->Release();
	}

	~XModel() {
		m_mesh->Release();
	}

	void draw(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, float ratio = 1.0f) {
		D3DXMATRIX world, trans, rotMat, scaling;
		D3DXMatrixScaling(&scaling, ratio, ratio, ratio);
		D3DXMatrixRotationYawPitchRoll(&rotMat, rot.y, rot.x, rot.z);
		D3DXMatrixTranslation(&trans, pos.x, pos.y, pos.z);

		D3DXMatrixIdentity(&world);
		D3DXMatrixMultiply(&world, &world, &scaling);
		D3DXMatrixMultiply(&world, &world, &rotMat);
		D3DXMatrixMultiply(&world, &world, &trans);

		draw(world);
	}

	void draw(const D3DXMATRIX& world) {
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

using XModelPtr = std::shared_ptr<XModel>;

class XModelManager {
public:
	XModelManager(LPDIRECT3DDEVICE9 d3dDevice) :
		m_d3dDevice(d3dDevice)
	{}
	void load(const std::string& filePath, const std::string& alias) {
		m_models[alias] = std::make_shared<XModel>(m_d3dDevice, filePath);
	}
	void clear() { m_models.clear(); }
	std::shared_ptr<XModel> get(const std::string& alias) {
		if (m_models.count(alias) == 0)
			throw std::out_of_range("Not Found " + alias);
		return m_models[alias];
	}
private:
	std::unordered_map<std::string, std::shared_ptr<XModel>> m_models;
	LPDIRECT3DDEVICE9 m_d3dDevice;
};

using XModelManagerPtr = std::shared_ptr<XModelManager>;
