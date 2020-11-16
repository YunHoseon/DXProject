#pragma once
#include <fmod.hpp>
#pragma comment(lib,"fmodex_vc.lib")
#include <string>
#include <map>

#define g_SoundManager	SoundManager::GetInstance()

using namespace std;
using namespace FMOD;

class SoundManager : public CSingleton<SoundManager>
{
private:
	INT				m_sfxCount;

	System * m_fmodSystem;
	Channel* m_bgmChannel;

	Sound* m_bgm;
	map<string, Sound*> m_soundHash;
	//map<string, Channel*> m_sfxChannel;
	vector<Channel*> m_sfxChannel;

private:
	void init();

public:
	SoundManager();
	~SoundManager();

	void AddSFX(string path, string musicName);
	void AddBGM(string path);
	void PlaySFX(string soundName);
	void PlayBGM();
	void Stop();
	void SetBGMSound(float fVoulum);

	void Destroy();

};

