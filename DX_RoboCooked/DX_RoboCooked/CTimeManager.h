#pragma once

#define g_pTimeManager CTimeManager::GetInstance()

class CTimeManager : public CSingleton<CTimeManager>
{
private:
	LARGE_INTEGER	m_dwLastUpdateTime;
	float	m_fElapsedTime;
	float	m_fFPS_Timer;
	int		m_FPS;
	friend CSingleton<CTimeManager>;
	CTimeManager();
	~CTimeManager();
public:

	void Update();
	float GetElapsedTime() { return m_fElapsedTime; }
	float GetLastUpdateTime() { return m_dwLastUpdateTime.QuadPart * 0.0000001f; }
	
};
