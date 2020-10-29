#pragma once

#define g_pTimeManager CTimeManager::GetInstance()

class CTimeManager : public CSingleton<CTimeManager>
{
private:
	//Singletone(CTimeManager);

private:
	DWORD	m_dwLastUpdateTime;
	float	m_fElapsedTime;

	CTimeManager();
	~CTimeManager();
public:
	void update();
	float GetElapsedTime();
	float GetLastUpdateTime();
	
};
