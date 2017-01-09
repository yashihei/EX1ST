#pragma once

#include "Common.h"

class Player {
public:
	Player(InputManagerPtr input)
		: m_inputManager(input)
	{
	}
	void update() {
	}
	void draw() {
	}
private:
	InputManagerPtr m_inputManager;
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
};

class Enemy : public Actor {
public:
	Enemy() {
	}
	void update() {
	}
	void draw() {
	}
private:
};

class Bullet {
public:
	Bullet() {
	}
	void update() {
	}
	void draw() {
	}
};

class Play2 : public Scene {
public:
	Play2(LPDIRECT3DDEVICE9 d3dDevice, InputManagerPtr input, SoundManagerPtr sound, RandomPtr random) :
		m_d3dDevice(d3dDevice), m_inputManager(input), m_soundManager(sound), m_random(random)
	{
	}
	void update() override {
		m_count++;
		m_player->update();
	}
	void draw() override {
		m_player->draw();
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	InputManagerPtr m_inputManager;
	SoundManagerPtr m_soundManager;
	RandomPtr m_random;

	int m_count = 0;
	PlayerPtr m_player;
};
