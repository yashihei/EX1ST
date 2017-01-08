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
	Player(LPDIRECT3DDEVICE9 d3dDevice, InputManagerPtr input, LPD3DXMESH mesh) :
		m_d3dDevice(d3dDevice), m_inputManager(input), m_mesh(mesh),
		m_pos(0, 0, 0)
	{
	}
	void update() {
		
	}
	void draw() {
		m_mesh->DrawSubset(0);
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	InputManagerPtr m_inputManager;
	LPD3DXMESH m_mesh;
	D3DXVECTOR3 m_pos;
};
using PlayerPtr = std::shared_ptr<Player>;

class Shot {
public:
private:
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

		D3DXCreateBox(d3dDevice, 5, 5, 5, &playerMesh, NULL);
	}
	void update() override {
		m_count++;
		m_background->update();
	}
	void draw() override {
		m_background->draw();
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	InputManagerPtr m_inputManager;
	SoundManagerPtr m_soundManager;
	RandomPtr m_random;

	CameraPtr m_camera;
	LightPtr m_light;
	LPD3DXMESH playerMesh;
	BackgroundPtr m_background;
	PlayerPtr m_player;

	int m_count;
};
