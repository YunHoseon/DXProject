#include "stdafx.h"
#include "CCrowdControl.h"

CCrowdControl::CCrowdControl() : m_fCCDownTime(999),m_fCCElapsedTime(0)
{
	g_EventManager->Attach(eEvent::Tick, this);
}

CCrowdControl::~CCrowdControl()
{
	g_EventManager->Detach(eEvent::Tick, this);
}

void CCrowdControl::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::Tick:
		UpdateTime(_value);
		break;
	}
}

void CCrowdControl::UpdateTime(void * _value)
{
	ST_TickEvent* data = static_cast<ST_TickEvent*>(_value);
	m_fCCElapsedTime += data->fElapsedTime;
}

bool CCrowdControl::IsEnd()
{
	if (m_fCCElapsedTime >= m_fCCDownTime)
		return true;
	return false;
}

