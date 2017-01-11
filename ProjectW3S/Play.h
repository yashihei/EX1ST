#pragma once

#include "Common.h"

class Player {
public:
	Player(InputManagerPtr input, ModelPtr model) :
		m_input(input), m_model(model),
		m_pos(0, 0.75, 0), m_rot(0, 0, 0), m_speed(), m_swingSpeed()
	{}
	void update() {
		//speed control
		if (m_input->isPressedUp())
			m_speed += 0.025f;
		else if (m_input->isPressedDown())
			m_speed -= 0.015f;
		m_speed *= 0.95f;

		//move control
		auto vec = D3DXVECTOR3(m_speed * std::cos(m_rot.y), 0.0f, -m_speed * std::sin(m_rot.y));
		m_pos += vec;
		m_pos.x = Clamp(m_pos.x, -50.0f, 50.0f);
		m_pos.z = Clamp(m_pos.z, -50.0f, 50.0f);
		
		//turn control
		if (m_input->isPressedLeft())
			m_swingSpeed -= 0.25f;
		else if (m_input->isPressedRight())
			m_swingSpeed += 0.25f;
		m_swingSpeed *= 0.9f;
		m_rot.y += D3DXToRadian(m_swingSpeed);

		//pose control
		m_rot.x = -m_speed * 0.5f;
		m_rot.z = m_swingSpeed * 0.5f;
	}
	void draw() {
		m_model->draw(m_pos, m_rot + D3DXVECTOR3(0, -D3DX_PI/2, 0), 0.1f);
	}

	D3DXVECTOR3 getPos() const { return m_pos; }
	D3DXVECTOR3 getRot() const { return m_rot; }
private:
	InputManagerPtr m_input;
	ModelPtr m_model;
	D3DXVECTOR3 m_pos, m_rot;
	float m_speed, m_swingSpeed;
};
using PlayerPtr = std::shared_ptr<Player>;

class Shot : public Actor {
public:
	Shot(SpritePtr sprite, CameraPtr camera, D3DXVECTOR3 pos, D3DXVECTOR3 vec) :
		m_sprite(sprite), m_camera(camera), m_pos(pos), m_vec(vec)
	{}
	void update() {
		m_count++;
		m_pos += m_vec;
		if (m_count > 300)
			kill();
	}
	void draw() {
		m_sprite->drawBillBoard(m_pos, m_camera);
	}
	D3DXVECTOR3 getPos() const { return m_pos; }
private:
	int m_count = 0;
	SpritePtr m_sprite;
	CameraPtr m_camera;
	D3DXVECTOR3 m_pos, m_vec;
};
using ShotsPtr = std::shared_ptr<ActorManager<Shot>>;

class Enemy : public Actor {
public:
	Enemy(ModelPtr model, D3DXVECTOR3 pos, PlayerPtr player) :
		m_model(model), m_pos(pos), m_rot(0, 0, 0), m_player(player)
	{}
	void update() {
		m_rot += D3DXVECTOR3(0, D3DXToRadian(3), D3DXToRadian(3));

		float rad = std::atan2(m_player->getPos().z - m_pos.z, m_player->getPos().x - m_pos.x);
		m_pos.z += std::sin(rad) * 0.05f;
		m_pos.x += std::cos(rad) * 0.05f;
	}
	void draw() {
		m_model->draw(m_pos, m_rot);
	}
	D3DXVECTOR3 getPos() const { return m_pos; }
private:
	ModelPtr m_model;
	D3DXVECTOR3 m_pos, m_rot;
	PlayerPtr m_player;
};
using EnemiesPtr = std::shared_ptr<ActorManager<Enemy>>;

class Score {
public:
	Score(FontPtr font) :
		m_font(font), m_score(0), m_viewScore(0)
	{}
	void addScore(int score) {
		m_score += score;
	}
	void update() {
		if (m_viewScore < m_score)
			m_viewScore += (m_score - m_viewScore) / 10 + 1;
	}
	void draw() {
		m_font->drawStr("SCORE:" + std::to_string(m_viewScore), { 12, 12 }, Color(0, 0, 0, 1).toD3Dcolor());
		m_font->drawStr("SCORE:" + std::to_string(m_viewScore), { 10, 10 });
	}
private:
	FontPtr m_font;
	int m_score, m_viewScore;
};
using ScorePtr = std::shared_ptr<Score>;

class TPSCamera {
public:
	TPSCamera(CameraPtr camera, D3DXVECTOR3 offset) :
		m_camera(camera), m_offset(offset)
	{}
	void update(D3DXVECTOR3 lookAt, D3DXVECTOR3 rot) {
		//カメラの動きを遅延させるため、一定フレームの動きを記録する
		m_tracks.push_back(std::make_pair(lookAt, rot));
		if (m_tracks.size() > 15)
			m_tracks.pop_front();

		auto nowLookAt = m_tracks[0].first;
		auto nowRot = m_tracks[0].second;

		D3DXMATRIX rotMat;
		D3DXMatrixRotationY(&rotMat, nowRot.y + D3DX_PI/2);
		
		D3DXVECTOR3 cameraPos;
		D3DXVec3TransformCoord(&cameraPos, &m_offset, &rotMat);
		cameraPos += nowLookAt;

		m_camera->moveTo(cameraPos);
		m_camera->lookAt(nowLookAt);
	}
private:
	CameraPtr m_camera;
	D3DXVECTOR3 m_offset;
	std::deque<std::pair<D3DXVECTOR3, D3DXVECTOR3>> m_tracks;
};
using TPSCameraPtr = std::shared_ptr<TPSCamera>;

class Play : public Scene {
public:
	Play(LPDIRECT3DDEVICE9 d3dDevice, InputManagerPtr input, SoundManagerPtr sound, RandomPtr random) :
		m_d3dDevice(d3dDevice), m_inputManager(input), m_soundManager(sound), m_random(random)
	{
		m_camera = std::make_shared<Camera>(m_d3dDevice, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0));
		m_tpsCamera = std::make_shared<TPSCamera>(m_camera, D3DXVECTOR3(0.0f, 3.5f, -10.0f));
		m_light = std::make_shared<Light>(m_d3dDevice, D3DXVECTOR3(0, -1, 0), D3DCOLORVALUE{1.0f, 1.0f, 1.0f, 1.0f}, D3DCOLORVALUE{0.2f, 0.2f, 0.2f, 1.0f}, D3DCOLORVALUE{1.0f, 1.0f, 1.0f, 1.0f});

		auto gridTex = std::make_shared<Texture>(m_d3dDevice, "dat/grid.png");
		m_groundSprite = std::make_shared<Sprite>(m_d3dDevice, gridTex, 100, 100);
		m_groundSprite->setDiffuse(Color(0, 0.5f, 1.0f, 0.4f).toD3Dcolor());
		m_groundSprite->setUV({ 0, 0, 50, 50 });
		m_groundSprite->setVtx();
		auto bulletTex = std::make_shared<Texture>(m_d3dDevice, "dat/bullet.png");
		m_bulletSprite = std::make_shared<Sprite>(m_d3dDevice, bulletTex, 2, 2);
		m_bulletSprite->setDiffuse(Color(1.0f, 0.5f, 0, 1.0f).toD3Dcolor());
		m_bulletSprite->setVtx();

		m_playerModel = std::make_shared<Model>(m_d3dDevice, "dat/airplane000.x");
		m_enemyModel = std::make_shared<Model>(m_d3dDevice, "dat/enemy.x");

		auto scoreFont = std::make_shared<Font>(m_d3dDevice, 30, "メイリオ", true);
		m_score = std::make_shared<Score>(scoreFont);

		m_player = std::make_shared<Player>(m_inputManager, m_playerModel);
		m_shots = std::make_shared<ActorManager<Shot>>();
		m_enemies = std::make_shared<ActorManager<Enemy>>();
	}
	void update() override {
		m_count++;
		m_player->update();
		m_shots->update();
		m_enemies->update();
		m_tpsCamera->update(m_player->getPos(), m_player->getRot());
		m_score->update();

		//shot
		if (m_inputManager->isPressedButton1() && m_count % 5 == 0) {
			auto vec = D3DXVECTOR3(3 * std::cos(m_player->getRot().y), 0.0f, -3 * std::sin(m_player->getRot().y));
			auto shot = std::make_shared<Shot>(m_bulletSprite, m_camera, m_player->getPos(), vec);
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
					m_score->addScore(100);
					break;
				}
			}
		}
	}
	void draw() override {
		m_player->draw();
		m_enemies->draw();

		m_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		m_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		m_groundSprite->draw({ 0, 0, 0 }, { D3DX_PI/2, 0, 0 });
		m_shots->draw();
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
	SpritePtr m_groundSprite, m_bulletSprite;
	ModelPtr m_playerModel, m_enemyModel;
	PlayerPtr m_player;
	ShotsPtr m_shots;
	EnemiesPtr m_enemies;
	ScorePtr m_score;
};
