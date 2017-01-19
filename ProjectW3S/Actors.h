#pragma once

#include "Common.h"

class Player {
public:
	Player(InputManagerPtr input, XModelPtr model) :
		m_input(input), m_model(model),
		m_pos(0, 0.75, 0), m_rot(0, 0, 0), m_speed(0), m_swingSpeed(0), m_count(0), m_hp(3), m_damageCount(0)
	{}
	void update() {
		m_count++; m_damageCount--;

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
		m_pos.y = 1.0f + std::cos(D3DXToRadian(m_count) * 3) * 0.1f;
		
		//turn control
		if (m_input->isPressedLeft())
			m_swingSpeed -= 0.25f;
		else if (m_input->isPressedRight())
			m_swingSpeed += 0.25f;
		m_swingSpeed *= 0.9f;
		m_rot.y += D3DXToRadian(m_swingSpeed);

		//pose control
		m_rot.x = m_speed * 0.5f;
		m_rot.z = -m_swingSpeed * 0.5f;
	}
	void draw() {
		if (m_damageCount > 0) {
			if (m_count % 10 < 5)
				m_model->draw(m_pos, m_rot + D3DXVECTOR3(0, D3DX_PI/2, 0));
		} else {
			m_model->draw(m_pos, m_rot + D3DXVECTOR3(0, D3DX_PI/2, 0));
		}
	}
	void damage() {
		if (m_damageCount < 0) {
			m_hp--;
			m_damageCount = 120;
		}
	}
	bool isAlived() {
		if (m_hp > 0)
			return true;
		else
			return false;
	}

	D3DXVECTOR3 getPos() const { return m_pos; }
	D3DXVECTOR3 getRot() const { return m_rot; }
	int getHP() const { return m_hp; }
private:
	InputManagerPtr m_input;
	XModelPtr m_model;
	D3DXVECTOR3 m_pos, m_rot;
	float m_speed, m_swingSpeed;
	int m_count, m_hp, m_damageCount;
};
using PlayerPtr = std::shared_ptr<Player>;

class Shot : public Actor {
public:
	Shot(SpritePtr sprite, CameraPtr camera, const D3DXVECTOR3& pos, const D3DXVECTOR3& vec) :
		m_sprite(sprite), m_camera(camera), m_pos(pos), m_vec(vec)
	{}
	void update() override {
		m_count++;
		m_pos += m_vec;
		if (m_count > 300)
			kill();
	}
	void draw() override {
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
	Enemy(XModelPtr model, const D3DXVECTOR3& pos, PlayerPtr player) :
		m_model(model), m_pos(pos), m_rot(0, 0, 0), m_player(player)
	{}
	void update() override {
		m_rot += D3DXVECTOR3(0, D3DXToRadian(2), D3DXToRadian(2));

		float rad = std::atan2(m_player->getPos().z - m_pos.z, m_player->getPos().x - m_pos.x);
		m_pos.z += std::sin(rad) * 0.075f;
		m_pos.x += std::cos(rad) * 0.075f;
	}
	void draw() override {
		m_model->draw(m_pos, m_rot);
	}
	D3DXVECTOR3 getPos() const { return m_pos; }
private:
	XModelPtr m_model;
	D3DXVECTOR3 m_pos, m_rot;
	PlayerPtr m_player;
};
using EnemiesPtr = std::shared_ptr<ActorManager<Enemy>>;

class Particle : public Actor {
public:
	Particle(SpritePtr sprite, CameraPtr camera, const D3DXVECTOR3& pos, const D3DXVECTOR3& vec, const Color& color) :
		m_sprite(sprite), m_camera(camera), m_pos(pos), m_vec(vec), m_color(color), m_alpha(1.0f)
	{}
	void update() override {
		m_vec *= 0.95f;
		m_alpha -= 0.020f;
		m_pos += m_vec;
		if (m_alpha < 0)
			kill();
	}
	void draw() override {
		for (int i = 0; i < 5; i++) {
			m_color.a = m_alpha/5 * 2;
			m_sprite->setDiffuse(m_color.toD3Dcolor());
			m_sprite->setVtx();
			m_sprite->drawBillBoard(m_pos + m_vec * i, m_camera, 0.75f + 0.05 * i);
		}
	}
private:
	SpritePtr m_sprite;
	CameraPtr m_camera;
	D3DXVECTOR3 m_pos, m_vec;
	Color m_color;
	float m_alpha;
};
using ParticlesPtr = std::shared_ptr<ActorManager<Particle>>;

class MiniMap {
public:
	MiniMap(PlayerPtr player, EnemiesPtr enemies) :
		m_player(player), m_enemies(enemies)
	{}
	void draw() {
	}
private:
	PlayerPtr m_player;
	EnemiesPtr m_enemies;
	D3DXVECTOR2 m_offset;
};

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
		m_font->drawStr("SCORE : " + std::to_string(m_viewScore), { 12, 12 }, Color(0, 0, 0, 1).toD3Dcolor());
		m_font->drawStr("SCORE : " + std::to_string(m_viewScore), { 10, 10 });
	}
private:
	FontPtr m_font;
	int m_score, m_viewScore;
};
using ScorePtr = std::shared_ptr<Score>;

class TPSCamera {
public:
	TPSCamera(CameraPtr camera, const D3DXVECTOR3& offset) :
		m_camera(camera), m_offset(offset)
	{}
	void update(const D3DXVECTOR3& lookAt, const D3DXVECTOR3& rot) {
		//�J�����̓�����x�������邽�߁A���t���[���̓������L�^����
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