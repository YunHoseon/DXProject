#pragma once

#define g_pTimeManager CTimeManager::GetInstance()

class CTimeManager : public CSingleton<CTimeManager>
{
private:
	DWORD	m_dwLastUpdateTime;
	float	m_fElapsedTime;
	friend CSingleton<CTimeManager>;
	CTimeManager();
	~CTimeManager();
public:

	void update();
	float GetElapsedTime();
	float GetLastUpdateTime();
	
};
