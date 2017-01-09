#pragma once

#include <d3dx9.h>
#include <memory>
#include <vector>
#include "Texture.h"

class Sprite2D {
public:
	Sprite2D(LPDIRECT3DDEVICE9 d3dDevice, TexturePtr tex, int col = 1, int row = 1)
		: m_d3dDevice(d3dDevice), m_texture(tex), m_col(col), m_row(row)
	{}

	void draw(D3DXVECTOR2 pos, float rad = 0.0f, float scale = 1.0f, const D3DXCOLOR& color = 0xFFffFFff, bool mirror = false) {
		draw({ 0, 0, 1, 1 }, pos, rad, scale, color, mirror);
	}

	void drawFrame(int index, D3DXVECTOR2 pos, float rad = 0.0f, float scale = 1.0f, const D3DXCOLOR& color = 0xFFffFFff, bool mirror = false) {
		float w = 1.0f / m_col;
		float h = 1.0f / m_row;

		index %= (m_col * m_row);

		TextureUV uv;
		uv.tu1 = w * (index % m_col);
		uv.tu2 = uv.tu1 + w;
		uv.tv1 = h * (index / m_col);
		uv.tv2 = uv.tv1 + h;

		draw(uv, pos, rad, scale, color, mirror);
	}

	void draw(TextureUV uv, D3DXVECTOR2 pos, float rad, float scale, const D3DXCOLOR& color, bool mirror) {
		auto texSize = m_texture->getSize();
		auto size = D3DXVECTOR2(texSize.x * (1.0f / m_col), texSize.y * (1.0f / m_row));

		std::vector<Sprite2DVtx> vtx {
			{{-size.x/2, -size.y/2, 0}, 1.0f, color, {uv.tu1, uv.tv1}},
			{{size.x/2, -size.y/2, 0}, 1.0f, color, {uv.tu2, uv.tv1}},
			{{-size.x/2, size.y/2, 0}, 1.0f, color, {uv.tu1, uv.tv2}},
			{{size.x/2, size.y/2, 0}, 1.0f, color, {uv.tu2, uv.tv2}},
		};

		if (mirror) {
			std::swap(vtx[0].t, vtx[1].t);
			std::swap(vtx[2].t, vtx[3].t);
		}

		for (int i = 0; i < 4; i++) {
			auto tPos = vtx[i].p;
			vtx[i].p.x = pos.x + scale * (tPos.x * std::cos(rad) - tPos.y * std::sin(rad));
			vtx[i].p.y = pos.y + scale * (tPos.x * std::sin(rad) + tPos.y * std::cos(rad));
		}

		m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		m_d3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		m_d3dDevice->SetFVF(Sprite2DVtxFVF);
		m_d3dDevice->SetTexture(0, m_texture->getTexPtr());
		m_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx.data(), sizeof(Sprite2DVtx));
		m_d3dDevice->SetTexture(0, NULL);
		m_d3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	TexturePtr m_texture;
	int m_col, m_row;

	struct Sprite2DVtx {
		D3DXVECTOR3 p;
		float rhw;
		DWORD color;
		D3DXVECTOR2 t;
	};
	static const WORD Sprite2DVtxFVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
};

using Sprite2DPtr = std::shared_ptr<Sprite2D>;
