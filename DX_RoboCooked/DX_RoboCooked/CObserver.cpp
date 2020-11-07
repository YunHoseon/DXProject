#include "stdafx.h"
#include "CObserver.h"

CObserver::~CObserver()
{
	std::set<EEvent>::iterator it = m_setSubsEvent.begin();
	CEventManager& manager = *CEventManager::GetInstance();
	for (; it != m_setSubsEvent.end(); it++)
	{
		manager.Detach(*it, this);
	}
}

void CObserver::Subscribe(EEvent eEvent)
{
	if (m_setSubsEvent.find(eEvent) != m_setSubsEvent.end())
		return;

	m_setSubsEvent.insert(eEvent);
	CEventManager::GetInstance()->Attach(eEvent, this);
}

void CObserver::UnSubscribe(EEvent eEvent)
{
	if (CEventManager::GetInstance()->Detach(eEvent, this))
	{
		m_setSubsEvent.erase(eEvent);
	}
}



