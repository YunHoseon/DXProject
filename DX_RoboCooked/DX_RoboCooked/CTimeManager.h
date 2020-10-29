#pragma once

#define g_pTimeManager CTimeManager::GetInstance()

class CTimeManager : public CSingleton<CTimeManager>
{
private:
	DWORD	m_dwLastUpdateTime;
	float	m_fElapsedTime;
public:
	CTimeManager();
	~CTimeManager();

	void update();
	float GetElapsedTime();
	float GetLastUpdateTime();
	
};
