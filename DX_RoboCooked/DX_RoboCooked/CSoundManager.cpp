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
	
	delete m_fmodSystem;
}

void SoundManager::init()
{
	m_sfxCount = 0;
	for (int i = 0; i < 5; i++)
	{
		Channel* sfx;
		m_sfxChannel.push_back(sfx);
	}

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
		m_fmodSystem->playSound(FMOD_CHANNEL_REUSE, m_soundHash[soundName], false, &m_sfxChannel[m_sfxCount]);

		if (m_sfxChannel.size() - 1 == m_sfxCount)
		{
			m_sfxCount = 0;
		}
		else
		{
			m_sfxCount++;
		}

	}
}

void SoundManager::Stop()
{
	m_bgmChannel->stop();
}

void SoundManager::SetBGMSound(float fVoulum)
{
	m_bgmChannel->setVolume(fVoulum);
}
