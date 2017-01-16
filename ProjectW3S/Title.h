#pragma once

#include "Common.h"

class Title : public Scene {
public:
	Title(LPDIRECT3DDEVICE9 d3dDevice, InputManagerPtr input, RandomPtr random)
		: m_d3dDevice(d3dDevice), m_inputManager(input), m_random(random)
	{
		m_titleFont = std::make_shared<Font>(m_d3dDevice, 100, "Orbitron", false);
		m_textFont = std::make_shared<Font>(m_d3dDevice, 32, "Orbitron", false);

		m_camera = std::make_shared<Camera>(m_d3dDevice, D3DXVECTOR3(0, 3.5, -10), D3DXVECTOR3(0, 0, 0));
		m_light = std::make_shared<Light>(m_d3dDevice, D3DXVECTOR3(0, -1, 0), D3DCOLORVALUE{1.0f, 1.0f, 1.0f, 1.0f}, D3DCOLORVALUE{0.5f, 0.5f, 0.5f, 1.0f}, D3DCOLORVALUE{1.0f, 1.0f, 1.0f, 1.0f});
		auto gridTex = std::make_shared<Texture>(m_d3dDevice, "assets/grid.png");
		m_groundSprite = std::make_shared<Sprite>(m_d3dDevice, gridTex, 100, 100);
		m_groundSprite->setDiffuse(Color(0, 0.5f, 1.0f, 0.6f).toD3Dcolor());
		m_groundSprite->setUV({ 0, 0, 30, 30 });
		m_groundSprite->setVtx();
	}
	void update() override {
		m_count++;
		if (m_inputManager->isClickedButton()) {
			changeScene(SceneType::Play);
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
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	InputManagerPtr m_inputManager;
	RandomPtr m_random;
	FontPtr m_titleFont, m_textFont;

	CameraPtr m_camera;
	LightPtr m_light;
	SpritePtr m_groundSprite;
	std::string m_titleText;
	float m_groundRot = 0.0f;
	int m_count = 0;
};
