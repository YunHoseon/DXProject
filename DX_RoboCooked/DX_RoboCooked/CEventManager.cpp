#include "stdafx.h"
#include "CEventListener.h"


CEventManager::CEventManager():CSingleton<CEventManager>()
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::Attach(EEvent eEvent, CEventListener* observer)
{
	m_mapEventMap[eEvent].insert(observer);
}

bool CEventManager::Detach(EEvent eEvent, CEventListener* observer)
{
	std::set<CEventListener*>::iterator it = std::find(m_mapEventMap[eEvent].begin(), m_mapEventMap[eEvent].end(), observer);
	if (it != m_mapEventMap[eEvent].end())
	{
		m_mapEventMap[eEvent].erase(it);
		return true;
	}
	return false;
}

void CEventManager::DetachAll(CEventListener* _observer)
{
	std::map<EEvent, std::set<CEventListener*>>::iterator it = m_mapEventMap.begin();
	while (it != m_mapEventMap.end())
	{
		for each(auto ob in it->second)
		{
			if (ob == _observer)
			{
				it->second.erase(ob);
			}	
		}
		++it;
	}
}


void CEventManager::CallEvent(EEvent eEvent, void* value)
{	
	std::set<CEventListener *>::iterator iterator = m_mapEventMap[eEvent].begin();

	while (iterator != m_mapEventMap[eEvent].end())
	{
		(*iterator)->OnEvent(eEvent, value);
		++iterator;
	}
}

void CEventManager::ErrorSend()
{
	std::cout << "publisher또는 subscriber 가 없습니다." << std::endl;
}
