#pragma once

#include "Common.h"

class Title : public Scene {
public:
	Title(LPDIRECT3DDEVICE9 d3dDevice, InputManagerPtr input, RandomPtr random) :
		m_d3dDevice(d3dDevice), m_inputManager(input), m_random(random),
		m_groundRot(0), m_count(0), m_fadeCount(0), m_fadeFlag(false)
	{
		m_titleFont = std::make_shared<Font>(m_d3dDevice, 100, "Orbitron", false);
		m_textFont = std::make_shared<Font>(m_d3dDevice, 32, "Orbitron", false);

		m_camera = std::make_shared<Camera>(m_d3dDevice, D3DXVECTOR3(0, 3.5, -10), D3DXVECTOR3(0, 0, 0));
		m_light = std::make_shared<Light>(m_d3dDevice, D3DXVECTOR3(0, -1, 0), D3DCOLORVALUE{1.0f, 1.0f, 1.0f, 1.0f}, D3DCOLORVALUE{0.5f, 0.5f, 0.5f, 1.0f}, D3DCOLORVALUE{1.0f, 1.0f, 1.0f, 1.0f});
		auto gridTex = std::make_shared<Texture>(m_d3dDevice, "assets/grid.png");
		m_groundSprite = std::make_shared<Sprite>(m_d3dDevice, gridTex, 100.0f, 100.0f);
		m_groundSprite->setDiffuse(Color(0, 0.5f, 1.0f, 0.6f).toD3Dcolor());
		m_groundSprite->setUV({ 0, 0, 30, 30 });
		m_groundSprite->setVtx();
	}
	void update() override {
		m_count++;

		if (m_fadeFlag) {
			m_fadeCount++;
			if (m_fadeCount > 100)
				changeScene(SceneType::Play);
		}
		if (m_inputManager->isClickedButton()) {
			m_fadeFlag = true;
			return;
		}

		m_groundRot += 0.0025f;

		m_titleText = "EX1ST";
		int cnt = 0;
		for (auto& c : m_titleText) {
			cnt++;
			if (m_count % 420 > (cnt * 20))
				continue;
			c = m_random->next(65, 90);
		}
	}
	void draw() override {
		m_titleFont->drawStr(m_titleText, { 30, 440 });
		m_textFont->drawStr("PUSH TO START", { 30, 540 });
		m_groundSprite->draw({ 0, 0, 0 }, { D3DX_PI/2, m_groundRot, 0 });
		if (m_fadeFlag)
			fade(255 / 100.0f * m_fadeCount);
	}
private:
	void fade(int alpha) {
		struct PlateVtx {
			D3DXVECTOR3 pos;
			float rhw;
			DWORD color;
		};
		float w = ScreenWidth; float h = ScreenHeight;
		std::vector<PlateVtx> vtx {
			{{0, 0, 0}, 1.0f, D3DCOLOR_ARGB(alpha, 0, 0, 0)},
			{{w, 0, 0}, 1.0f, D3DCOLOR_ARGB(alpha, 0, 0, 0)},
			{{0, h, 0}, 1.0f, D3DCOLOR_ARGB(alpha, 0, 0, 0)},
			{{w, h, 0}, 1.0f, D3DCOLOR_ARGB(alpha, 0, 0, 0)},
		};
		m_d3dDevice->SetTexture(0, NULL);
		m_d3dDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
		m_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vtx.data(), sizeof(PlateVtx));
	}

	LPDIRECT3DDEVICE9 m_d3dDevice;
	InputManagerPtr m_inputManager;
	RandomPtr m_random;
	FontPtr m_titleFont, m_textFont;

	CameraPtr m_camera;
	LightPtr m_light;
	SpritePtr m_groundSprite;
	std::string m_titleText;
	float m_groundRot;
	int m_count, m_fadeCount;
	bool m_fadeFlag;
};
