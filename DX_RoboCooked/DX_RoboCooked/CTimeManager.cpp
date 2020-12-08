#include "stdafx.h"
#include "CTimeManager.h"

CTimeManager::CTimeManager(): CSingleton<CTimeManager>(), m_fElapsedTime(0)
{
	QueryPerformanceCounter(&m_dwLastUpdateTime);
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::Update()
{
	//DWORD dwCurrentTime = GetTickCount();
	//m_fElapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.0f;
	//m_dwLastUpdateTime = dwCurrentTime;


	LARGE_INTEGER CurTime, frequency, DeltaTime;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&CurTime);
	DeltaTime.QuadPart = (CurTime.QuadPart - m_dwLastUpdateTime.QuadPart) * 1000000;
	DeltaTime.QuadPart /= frequency.QuadPart;

	m_fElapsedTime = DeltaTime.QuadPart * 0.000001f;

	//m_fFPS_Timer += m_fElapsedTime;
	//static int Cnt = 0;
	//Cnt++;

	//if (m_fFPS_Timer > 1)
	//{
	//	m_fFPS_Timer = 0;
	//	m_FPS = Cnt;
	//	Cnt = 0;
	//}

	m_dwLastUpdateTime = CurTime;
	ST_TickEvent data;
	data.fElapsedTime = m_fElapsedTime;
	g_EventManager->CallEvent(eEvent::Tick, (void*)&data);


}

float CTimeManager::GetElapsedTime()
{
	return m_fElapsedTime;
}

float CTimeManager::GetLastUpdateTime()
{
	return m_dwLastUpdateTime.QuadPart * 0.0000001f;
}
