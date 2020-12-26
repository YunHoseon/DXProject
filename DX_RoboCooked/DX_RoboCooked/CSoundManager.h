#pragma once
#include "include/fmod.hpp"
#pragma comment(lib,"fmodex_vc.lib")
#include <string>
#include <map>

#define g_SoundManager	SoundManager::GetInstance()

//using namespace std;
using namespace FMOD;

class SoundManager : public CSingleton<SoundManager>
{
private:
	//INT				m_sfxCount;

	System * m_fmodSystem;
	Channel* m_bgmChannel;

	Sound* m_bgm;
	map<string, Sound*> m_soundHash;
	//map<string, Channel*> m_sfxChannel;
	map<string, Channel*> m_sfxChannel;

private:
	void init();
	friend CSingleton<SoundManager>;
	SoundManager();
	~SoundManager();
public:

	void AddSFX(string path, string musicName);
	void AddBGM(string path);
	void PlaySFX(string soundName);
	void StopSFX(string soundName);
	bool IsPlayingSFX(string soundName);
	void PlayBGM();
	void StopBGM();
	void SetBGMSound(float fVolume);

	void Destroy();

};

