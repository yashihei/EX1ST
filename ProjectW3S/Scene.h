#pragma once

#include <memory>

enum class SceneType {
	Title, Play, Result, Demo, None
};

class Scene {
public:
	virtual ~Scene() = default;
	virtual void update() = 0;
	virtual void draw() = 0;
	SceneType nextScene() {
		return m_next;
	}
protected:
	void changeScene(SceneType type) {
		m_next = type;
	}
private:
	SceneType m_next = SceneType::None;
};

using ScenePtr = std::shared_ptr<Scene>;
