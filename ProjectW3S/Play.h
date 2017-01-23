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
		m_texureManager = std::make_shared<TextureManager>(m_d3dDevice);
		m_texureManager->load("assets/grid.png", "grid");
		m_texureManager->load("assets/circle.png", "circle");
		m_texureManager->load("assets/shadow.png", "shadow");
		m_texureManager->load("assets/rader.png", "rader");
		m_texureManager->load("assets/point.png", "point");
		m_texureManager->load("assets/scanline.png", "scanline");

		//create sprites
		m_groundSprite = std::make_shared<Sprite>(m_d3dDevice, m_texureManager->get("grid"), 100.0f, 100.0f);
		m_groundSprite->setDiffuse(Color(0, 0.5f, 1.0f, 0.6f).toD3Dcolor());
		m_groundSprite->setUV({ 0, 0, 30, 30 });
		m_groundSprite->setVtx();

		m_bulletSprite = std::make_shared<Sprite>(m_d3dDevice, m_texureManager->get("circle"), 64);
		m_bulletSprite->setDiffuse(Color(1.0f, 0.7f, 0, 1.0f).toD3Dcolor());
		m_bulletSprite->setVtx();

		m_shadowSprite = std::make_shared<Sprite>(m_d3dDevice, m_texureManager->get("shadow"), 64);
		m_shadowSprite->setDiffuse(Color(1.0f, 1.0f, 1.0f, 0.15f).toD3Dcolor());
		m_shadowSprite->setVtx();

		m_particleSprite = std::make_shared<Sprite>(m_d3dDevice, m_texureManager->get("circle"), 64);

		//ui sprites
		m_raderSprite = std::make_shared<Sprite2D>(m_d3dDevice, m_texureManager->get("rader"));
		m_pointSprite = std::make_shared<Sprite2D>(m_d3dDevice, m_texureManager->get("point"));
		m_scanSprite = std::make_shared<Sprite2D>(m_d3dDevice, m_texureManager->get("scanline"));

		//load model
		m_XModelManager = std::make_shared<XModelManager>(m_d3dDevice);
		m_XModelManager->load("assets/player.x", "player");
		m_XModelManager->load("assets/enemy.x", "enemy");

		m_textFont = std::make_shared<Font>(m_d3dDevice, 30, "Orbitron", false);

		//create actors
		m_player = std::make_shared<Player>(m_inputManager, m_XModelManager->get("player"));
		m_shots = std::make_shared<ActorManager<Shot>>();
		m_enemies = std::make_shared<ActorManager<Enemy>>();
		m_particles = std::make_shared<ActorManager<Particle>>();
		m_score = std::make_shared<Score>(m_textFont);

		m_soundManager->play("bgm", 1.0f, true);
	}
	void update() override {
		m_count++;
		if (!m_player->isAlived()) {
			m_soundManager->stop("bgm");
			changeScene(SceneType::Title);
			return;
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
			m_soundManager->play("shoot", 0.35f);
		}

		//spown
		if (m_count % 60 == 0) {
			//TODO:—N‚«‚ð‰“‚­‚É
			auto enemy = std::make_shared<Enemy>(m_XModelManager->get("enemy"), D3DXVECTOR3(m_random->nextPlusMinus(50.0f), 1, m_random->nextPlusMinus(50.0f)), m_player);
			m_enemies->add(enemy);
		}
		
		//shot vs enemy
		for (auto& shot : *m_shots) {
			for (auto& enemy : *m_enemies) {
				if (IsCollied(shot->getPos(), enemy->getPos(), 1, 1)) {
					enemy->kill();
					shot->kill();
					createParticle(enemy->getPos(), 35);
					m_score->addScore(100);
					m_soundManager->play("bom", 0.5f);
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

	void createParticle(const D3DXVECTOR3& pos, int num) {
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
		EnebleAddBlend(m_d3dDevice);
		m_groundSprite->draw({ 0, 0, 0 }, { D3DX_PI/2, 0, 0 });
		m_shots->draw();

		DisableZBuf(m_d3dDevice);
		EnebleSubBlend(m_d3dDevice);
		m_shadowSprite->draw({ m_player->getPos().x, 0, m_player->getPos().z }, { D3DX_PI / 2, 0, 0 }, 2.5f);
		EnebleAddBlend(m_d3dDevice);
		m_particles->draw();
		EnebleZBuf(m_d3dDevice);

		EnebleNormalBlend(m_d3dDevice);

		//ui
		const D3DXVECTOR2 offset(ScreenWidth - 64 - 15, 64 + 15);
		m_raderSprite->draw(offset, 0, 1.0f, Color(1, 1, 1, 0.75f).toD3Dcolor());
		for (auto& enemy : *m_enemies) {
			auto pos = m_player->getPos() - enemy->getPos();
			auto pos2d = D3DXVECTOR2(pos.x, pos.z);
			if (D3DXVec2Length(&pos2d) > 64)
				continue;
			D3DXMATRIX rot;
			D3DXMatrixRotationY(&rot, -m_player->getRot().y);
			D3DXVec3TransformCoord(&pos, &pos, &rot);
			m_pointSprite->draw(offset + D3DXVECTOR2(pos.z, pos.x), 0, 0.5f, Color(1, 0.25, 0, 0.75f).toD3Dcolor());
		}
		EnebleAddBlend(m_d3dDevice);
		m_scanSprite->draw(offset, 0.02f * m_count);
		EnebleNormalBlend(m_d3dDevice);

		m_score->draw();
		m_textFont->drawStr("LIFE :", { 15, 40 });
		m_textFont->drawStr(std::to_string(m_player->getHP()), {95, 40}, Color(1.0f, 0.5f, 0.5f).toD3Dcolor());
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
	TextureManagerPtr m_texureManager;
	SpritePtr m_groundSprite, m_bulletSprite, m_particleSprite, m_shadowSprite;
	Sprite2DPtr m_raderSprite, m_pointSprite, m_scanSprite;
	XModelManagerPtr m_XModelManager;
	FontPtr m_textFont;
	PlayerPtr m_player;
	ShotsPtr m_shots;
	EnemiesPtr m_enemies;
	ParticlesPtr m_particles;
	ScorePtr m_score;
};
