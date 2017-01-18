#pragma once

#include "Common.h"
#include "Actors.h"

class Play : public Scene {
public:
	Play(LPDIRECT3DDEVICE9 d3dDevice, InputManagerPtr input, SoundManagerPtr sound, RandomPtr random) :
		m_d3dDevice(d3dDevice), m_inputManager(input), m_soundManager(sound), m_random(random)
	{
		m_camera = std::make_shared<Camera>(m_d3dDevice, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		m_tpsCamera = std::make_shared<TPSCamera>(m_camera, D3DXVECTOR3(0.0f, 3.0f, -7.5f));
		m_light = std::make_shared<Light>(m_d3dDevice, D3DXVECTOR3(0, -1, 0), D3DCOLORVALUE{1.0f, 1.0f, 1.0f, 1.0f}, D3DCOLORVALUE{0.5f, 0.5f, 0.5f, 1.0f}, D3DCOLORVALUE{1.0f, 1.0f, 1.0f, 1.0f});

		//load tex and create sprite
		auto gridTex = std::make_shared<Texture>(m_d3dDevice, "assets/grid.png");
		m_groundSprite = std::make_shared<Sprite>(m_d3dDevice, gridTex, 100, 100);
		m_groundSprite->setDiffuse(Color(0, 0.5f, 1.0f, 0.6f).toD3Dcolor());
		m_groundSprite->setUV({ 0, 0, 30, 30 });
		m_groundSprite->setVtx();
		auto circleTex = std::make_shared<Texture>(m_d3dDevice, "assets/circle.png");
		m_bulletSprite = std::make_shared<Sprite>(m_d3dDevice, circleTex, 2, 2);
		m_bulletSprite->setDiffuse(Color(1.0f, 0.7f, 0, 1.0f).toD3Dcolor());
		m_bulletSprite->setVtx();
		m_particleSprite = std::make_shared<Sprite>(m_d3dDevice, circleTex, 0.5f, 0.5f);

		//load model
		m_playerModel = std::make_shared<XModel>(m_d3dDevice, "assets/player.x");
		m_enemyModel = std::make_shared<XModel>(m_d3dDevice, "assets/enemy.x");

		m_textFont = std::make_shared<Font>(m_d3dDevice, 30, "Orbitron", false);
		m_score = std::make_shared<Score>(m_textFont);

		m_player = std::make_shared<Player>(m_inputManager, m_playerModel);
		m_shots = std::make_shared<ActorManager<Shot>>();
		m_enemies = std::make_shared<ActorManager<Enemy>>();
		m_particles = std::make_shared<ActorManager<Particle>>();
	}
	void update() override {
		m_count++;
		if (!m_player->isAlived()) {
			changeScene(SceneType::Title);
		}

		m_player->update();
		m_shots->update();
		m_enemies->update();
		m_particles->update();
		m_tpsCamera->update(m_player->getPos(), m_player->getRot());
		m_score->update();

		//shot
		if (m_inputManager->isPressedButton() && m_count % 5 == 0) {
			auto vec = D3DXVECTOR3(3 * std::cos(m_player->getRot().y), 0.0f, -3 * std::sin(m_player->getRot().y));
			auto shot = std::make_shared<Shot>(m_bulletSprite, m_camera, m_player->getPos() + vec, vec);
			m_shots->add(shot);
		}

		//spown
		if (m_count % 100 == 0) {
			auto enemy = std::make_shared<Enemy>(m_enemyModel, D3DXVECTOR3(m_random->nextPlusMinus(50), 1, m_random->nextPlusMinus(50)), m_player);
			m_enemies->add(enemy);
		}
		
		//shot vs enemy
		for (auto& shot : *m_shots) {
			for (auto& enemy : *m_enemies) {
				if (IsCollied(shot->getPos(), enemy->getPos(), 1, 1)) {
					enemy->kill();
					shot->kill();
					createParticle(enemy->getPos(), 50);
					m_score->addScore(100);
					break;
				}
			}
		}

		//enemy vs player
		for (auto& enemy : *m_enemies) {
			if (IsCollied(enemy->getPos(), m_player->getPos(), 1, 1)) {
				m_player->damage();
				break;
			}
		}
	}

	void createParticle(D3DXVECTOR3 pos, int num) {
		for (int i = 0; i < num; i++) {
			auto vec = D3DXVECTOR3(m_random->next(1.0f), 0, 0);

			D3DXMATRIX rot;
			D3DXMatrixRotationYawPitchRoll(&rot, m_random->next(D3DX_PI * 2), m_random->next(D3DX_PI * 2), m_random->next(D3DX_PI * 2));
			D3DXVec3TransformCoord(&vec, &vec, &rot);

			auto particle = std::make_shared<Particle>(m_particleSprite, m_camera, pos, vec, Color(1.0f, 0.5f, 1.0f, 1.0f));
			m_particles->add(particle);
		}
	}

	void draw() override {
		m_player->draw();
		m_enemies->draw();

		//draw sprites
		m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		m_groundSprite->draw({ 0, 0, 0 }, { D3DX_PI/2, 0, 0 });
		m_shots->draw();
		m_d3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		m_particles->draw();
		m_d3dDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		
		m_score->draw();
	}
private:
	LPDIRECT3DDEVICE9 m_d3dDevice;
	InputManagerPtr m_inputManager;
	SoundManagerPtr m_soundManager;
	RandomPtr m_random;

	int m_count = 0;
	CameraPtr m_camera;
	TPSCameraPtr m_tpsCamera;
	LightPtr m_light;
	SpritePtr m_groundSprite, m_bulletSprite, m_particleSprite;
	XModelPtr m_playerModel, m_enemyModel;
	FontPtr m_textFont;
	PlayerPtr m_player;
	ShotsPtr m_shots;
	EnemiesPtr m_enemies;
	ParticlesPtr m_particles;
	ScorePtr m_score;
};
