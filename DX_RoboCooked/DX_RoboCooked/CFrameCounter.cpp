#include "stdafx.h"
#include "CFrameCounter.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


CFrameCounter::CFrameCounter(): m_nFPS(0), m_nCount(0)
{
	m_nStartTime = timeGetTime();
}

void CFrameCounter::Update()
{
	m_nCount++;
	time_t nCurrentTime = timeGetTime();
	if ( nCurrentTime >= (m_nStartTime + 1000 /*- m_nJunk*/))
	{
		m_nFPS = m_nCount;
		m_nCount = 0;
		m_nStartTime = nCurrentTime;
	}
}
