#include "stdafx.h"
#include "CObserver.h"

CObserver::~CObserver()
{
	/*std::set<EEvent>::iterator it = m_setSubsEvent.begin();
	CEventManager& manager = *CEventManager::GetInstance();
	for (; it != m_setSubsEvent.end(); it++)
	{
		manager.Detach(*it, this);
	}*/
}


