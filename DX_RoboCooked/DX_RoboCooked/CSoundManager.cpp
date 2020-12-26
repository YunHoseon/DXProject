#include "stdafx.h"



SoundManager::SoundManager()
{
	init();
}


SoundManager::~SoundManager()
{
	
}

void SoundManager::Destroy()
{

	for each(auto it in m_soundHash)
	{
		it.second->release();
	}
}

void SoundManager::init()
{
	System_Create(&m_fmodSystem);
	m_fmodSystem->init(10, FMOD_INIT_NORMAL, NULL);
}

void SoundManager::AddBGM(string path)
{
	m_fmodSystem->createStream(path.c_str(), FMOD_LOOP_NORMAL, NULL, &m_bgm); //¹è°æÀº createStream
}

void SoundManager::AddSFX(string path, string soundName)
{
	m_fmodSystem->createSound(path.c_str(), FMOD_DEFAULT, NULL, &m_soundHash[soundName]);
	/*Channel* sfx = nullptr;
	m_sfxChannel[soundName] = sfx*/;
}

void SoundManager::PlayBGM()
{
	m_fmodSystem->playSound(FMOD_CHANNEL_REUSE, m_bgm, false, &m_bgmChannel);
}

void SoundManager::PlaySFX(string soundName)
{
	if (m_soundHash[soundName] != NULL)
	{		
		m_fmodSystem->playSound(FMOD_CHANNEL_REUSE, m_soundHash[soundName], false, &m_sfxChannel[soundName]);
	}
}

void SoundManager::StopSFX(string soundName)
{
	if (m_sfxChannel[soundName] != NULL)
	{
		m_sfxChannel[soundName]->stop();
	}
}

bool SoundManager::IsPlayingSFX(string soundName)
{
	bool b = false;
	if (m_sfxChannel[soundName] != nullptr)
	{
		m_sfxChannel[soundName]->isPlaying(&b);
	}
	return b;
}

void SoundManager::StopBGM()
{
	m_bgmChannel->stop();
}

void SoundManager::SetBGMSound(float fVolume)
{
	m_bgmChannel->setVolume(fVolume);
}
