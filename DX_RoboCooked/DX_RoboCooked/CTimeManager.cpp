#include "stdafx.h"
#include "CTimeManager.h"

CTimeManager::CTimeManager(): CSingleton<CTimeManager>(), m_dwLastUpdateTime(0), m_fElapsedTime(0)
{
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.0f;
	m_dwLastUpdateTime = dwCurrentTime;
}

float CTimeManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

float CTimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime / 1000.0f;
}
