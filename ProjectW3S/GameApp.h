#pragma once

#include "Common.h"

class GameApp {
public:
	GameApp(HWND hWnd, HINSTANCE hInstance, bool fullScreen);
	void run();
private:
	void changeScene(SceneType type);

	GraphicsPtr m_graphics;
	SoundManagerPtr m_soundManager;
	InputManagerPtr m_inputManager;
	FPSControlerPtr m_fpsControler;
	RandomPtr m_random;
	ScenePtr m_scene;
};
