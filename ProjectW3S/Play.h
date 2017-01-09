#pragma once

#include "Common.h"

class Background {
public:
	Background(LPDIRECT3DDEVICE9 d3dDevice) : m_count(0) {
		TexturePtr backTex = std::make_shared<Texture>(d3dDevice, "dat/grid.png");
		m_sprite = std::make_shared<Sprite>(d3dDevice, backTex, 128);
	}
	void update() {
		m_count++;
		m_sprite->setDiffuse(HSV(1.0f/3600*m_count, 1.0f, 1.0f).toColor(0.8f).toD3Dcolor());
		m_sprite->setUV({0, m_count/300.0f, 1.0f, 1.0f + m_count/300.0f});
		m_sprite->setVtx();
	}
	void draw() {
		m_sprite->draw({ 0, -2, 0 }, 90, 0, 180);
		m_sprite->draw({ 0, 2, 0 }, -90, 0, 0);
		m_sprite->draw({ -2, 0, 0 }, 0, -90, 90);
		m_sprite->draw({ 2, 0, 0 }, 0, 90, -90);
		m_sprite->draw({ 0, -2, 4 }, 90, 0, 180);
		m_sprite->draw({ 0, 2, 4 }, -90, 0, 0);
		m_sprite->draw({ -2, 0, 4 }, 0, -90, 90);
		m_sprite->draw({ 2, 0, 4 }, 0, 90, -90);
	}
private:
	SpritePtr m_sprite;
	int m_count;
};
using BackgroundPtr = std::shared_ptr<Background>;

class Player {
public:
	Player(LPDIRECT3DDEVICE9 d3dDevice, InputManagerPtr input, ModelPtr model) :
		m_d3dDevice(d3dDevice), m_inputManager(input), m_model(model),
		m_pos(0, 0, 0), m_count(0)
	{
	}
	void update() {
		m_count++;

		Vector2 dir;
		if (m_inputManager->isPressedUp())
			dir.y = 1;
		else if (m_inputManager->isPressedDown())
			dir.y = -1;
		if (m_inputManager->isPressedLeft())
			dir.x = -1;
		else if (m_inputManager->isPressedRight())
			dir.x = 1;

		dir.normalized();
		dir *= 0.05f;
		m_pos.x += dir.x; m_pos.y += dir.y;

		m_pos.x = Clamp(m_pos.x, -2.0f, 2.0f);
		m_pos.y = Clamp(m_pos.y, -2.0f, 2.0f);
	}
	void draw() {
		m_model->draw(m_pos, 0, 0, m_count);
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	InputManagerPtr m_inputManager;
	ModelPtr m_model;
	D3DXVECTOR3 m_pos;
	int m_count;
};
using PlayerPtr = std::shared_ptr<Player>;

class Shot : public Actor {
public:
	Shot() {
	}
	void update() {
	}
	void draw() {
	}
private:
	D3DXVECTOR3 m_pos;
	SpritePtr m_sprite;
};

class Enemy {
public:
private:
};

class Play : public Scene {
public:
	Play(LPDIRECT3DDEVICE9 d3dDevice, InputManagerPtr input, SoundManagerPtr sound, RandomPtr random) :
		m_d3dDevice(d3dDevice), m_inputManager(input), m_soundManager(sound), m_random(random),
		m_count(0)
	{
		m_camera = std::make_shared<Camera>(d3dDevice, D3DXVECTOR3(0, 0, -5), D3DXVECTOR3(0, 0, 0));
		m_light = std::make_shared<Light>(d3dDevice, D3DXVECTOR3(0, -1, 1), D3DCOLORVALUE{1.0f, 1.0f, 1.0f});

		m_background = std::make_shared<Background>(d3dDevice);

		ModelPtr playerModel = std::make_shared<Model>(d3dDevice, "dat/model.x");
		m_player = std::make_shared<Player>(m_d3dDevice, input, playerModel);
	}
	void update() override {
		m_count++;
		m_background->update();
		m_player->update();
	}
	void draw() override {
		m_background->draw();
		m_player->draw();
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	InputManagerPtr m_inputManager;
	SoundManagerPtr m_soundManager;
	RandomPtr m_random;

	CameraPtr m_camera;
	LightPtr m_light;
	BackgroundPtr m_background;
	PlayerPtr m_player;

	int m_count;
};
