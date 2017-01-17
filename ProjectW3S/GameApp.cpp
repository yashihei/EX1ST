#include "GameApp.h"

#include "Play.h"
#include "Title.h"

GameApp::GameApp(HWND hWnd, HINSTANCE hInstance, bool fullScreen) {
	m_graphics = std::make_shared<Graphics>(hWnd, fullScreen);
	m_soundManager = std::make_shared<SoundManager>();
	m_inputManager = std::make_shared<InputManager>(hWnd, hInstance);
	m_fpsControler = std::make_shared<FPSControler>(60);
	m_random = std::make_shared<Random>();
	Font::addFont("assets/orbitron-light.otf");
	changeScene(SceneType::Title);
}

void GameApp::run() {
	m_inputManager->update();

	m_scene->update();
	if (m_scene->nextScene() != SceneType::None)
		changeScene(m_scene->nextScene());

	if (SUCCEEDED(m_graphics->beginScene(10, 20, 30))) {
		m_scene->draw();
		m_graphics->endScene();
	}
	m_graphics->present();
	m_fpsControler->wait();
}

void GameApp::changeScene(SceneType type) {
	switch (type) {
	case SceneType::Title:
		m_scene = std::make_shared<Title>(m_graphics->getDevice(), m_inputManager, m_random);
		break;
	case SceneType::Play:
		m_scene = std::make_shared<Play>(m_graphics->getDevice(), m_inputManager, m_soundManager, m_random);
		break;
	}
}
