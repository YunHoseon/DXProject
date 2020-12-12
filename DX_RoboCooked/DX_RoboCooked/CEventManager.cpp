#include "stdafx.h"
#include "CEventListener.h"

static std::mutex cEventMutex;

CEventManager::CEventManager():CSingleton<CEventManager>()
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::Attach(eEvent eEvent, CEventListener* observer)
{
	cEventMutex.lock();
	m_mapEventMap[eEvent].insert(observer);
	cEventMutex.unlock();
}

bool CEventManager::Detach(eEvent eEvent, CEventListener* observer)
{
	std::set<CEventListener*>::iterator it = m_mapEventMap[eEvent].find(observer);
	if (it != m_mapEventMap[eEvent].end())
	{
		cEventMutex.lock();
		m_mapEventMap[eEvent].erase(it);
		cEventMutex.unlock();

		return true;
	}
	return false;
}

void CEventManager::DetachAll(CEventListener* _observer)
{
	std::map<eEvent, std::set<CEventListener*>>::iterator it = m_mapEventMap.begin();
	while (it != m_mapEventMap.end())
	{
		if (it->second.find(_observer) != it->second.end())
		{
			cEventMutex.lock();
			it->second.erase(_observer);
			cEventMutex.unlock();

		}
		++it;
	}
}


void CEventManager::CallEvent(eEvent eEvent, void* value)
{	
	std::set<CEventListener *>::iterator it = m_mapEventMap[eEvent].begin();

	while (it != m_mapEventMap[eEvent].end())
	{
		(*it)->OnEvent(eEvent, value);

		++it;

		
	}
}

void CEventManager::ErrorSend()
{
	_DEBUG_COMMENT std::cout << "publisher또는 subscriber 가 없습니다." << std::endl;
}
