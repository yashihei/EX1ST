#pragma once

#include <XAudio2.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

class Sound;
struct SoundBuffer;

class SoundManager {
public:
	SoundManager();
	~SoundManager();
	void load(const std::string& filePath, const std::string& alias);
	void play(const std::string& alias, float volume = 1.0f, bool loop = false);
	void stop(const std::string& alias);
	void mute(bool enable) { m_muting = enable; }
	void clear() { m_sounds.clear(); }
private:
	IXAudio2* m_xAudio;
	IXAudio2MasteringVoice* m_masteringVoice;
	std::unordered_map<std::string, std::shared_ptr<Sound>> m_sounds;
	bool m_muting;
};

using SoundManagerPtr = std::shared_ptr<SoundManager>;

class Sound {
public:
	Sound(IXAudio2* xAudio, const std::string& filePath);
	~Sound();
	void init(bool loop = false);
	void play(float volume = 1.0f, float freqRatio = 1.0f);
	void stop();
private:
	IXAudio2* m_xAudio;
	IXAudio2SourceVoice* m_sourceVoice;
	std::shared_ptr<SoundBuffer> m_soundBuffer;
};

struct SoundBuffer {
	explicit SoundBuffer(const std::string& filePath);
	~SoundBuffer();
	DWORD size;
	WAVEFORMATEX waveFormatEx;
	std::vector<BYTE> buffer;
};
