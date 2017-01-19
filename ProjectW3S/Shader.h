#pragma once

#include <d3dx9.h>
#include <string>
#include <memory>

class Shader {
public:
	Shader(LPDIRECT3DDEVICE9 d3dDevice, const std::string& filePath) :
		m_d3dDevice(d3dDevice)
	{
		LPD3DXBUFFER err = NULL;
		HRESULT hr = D3DXCreateEffectFromFileA(m_d3dDevice, filePath.c_str(), NULL, NULL, 0, NULL, &m_effect, &err);
		if (FAILED(hr))
			throw std::runtime_error("Failed load " + filePath);

		m_technique = m_effect->GetTechniqueByName("TShader");
	}

	~Shader() {
		if (m_effect)
			m_effect->Release();
	}

	void begin() {
		m_effect->SetTechnique(m_technique);
		m_effect->Begin(NULL, 0);
	}

	void beginPass(UINT pass) {
		m_effect->BeginPass(pass);
	}

	void endPass() {
		m_effect->EndPass();
	}

	void end() {
		m_effect->End();
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	LPD3DXEFFECT m_effect;

	D3DXHANDLE m_technique;
};

using ShaderPtr = std::shared_ptr<Shader>;
