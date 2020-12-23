#include "stdafx.h"
#include "CThreadManager.h"

CThreadManager::CThreadManager():
	m_isThreadStop(false)
{
}

CThreadManager::~CThreadManager()
{
	
}

void CThreadManager::JoinAllThread()
{
	m_mutex.lock();
	m_isThreadStop = true;
	for (int i = 0; i < m_vecThread.size(); ++i)
	{
		if (m_vecThread[i].joinable())
			m_vecThread[i].join();
	}
	m_vecThread.clear();
	m_isThreadStop = false;
	m_mutex.unlock();
}

void CThreadManager::Destroy()
{
	JoinAllThread();
}
