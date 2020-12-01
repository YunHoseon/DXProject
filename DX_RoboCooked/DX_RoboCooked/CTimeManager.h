#pragma once

#define g_pTimeManager CTimeManager::GetInstance()

class CTimeManager : public CSingleton<CTimeManager>
{
private:
	LARGE_INTEGER	m_dwLastUpdateTime;
	float	m_fElapsedTime;
	friend CSingleton<CTimeManager>;
	CTimeManager();
	~CTimeManager();
public:

	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();
	
};
