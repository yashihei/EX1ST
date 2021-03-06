#pragma once

#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <memory>

class Time {
public:
	Time()
		: m_frameCount(0), m_prevTime(0), m_deltaTime(0)
	{
		m_prevTime = timeGetTime();
	}
	~Time() {}
	void update() {
		DWORD nowTime = timeGetTime();
		m_deltaTime = nowTime - m_prevTime;
		m_prevTime = nowTime;
		m_frameCount++;
	}
	float getDeltaTime() const { return m_deltaTime/1000.0f; }
	int getFrameCount() const { return m_frameCount; }
private:
	int m_frameCount;
	DWORD m_prevTime, m_deltaTime;
};

using TimePtr = std::shared_ptr<Time>;
