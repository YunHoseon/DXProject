#include "stdafx.h"
#include "CUIReady.h"
#include "CUIReadyBoard.h"
#include "IInteractCenter.h"

CUIReady::CUIReady(D3DXVECTOR2 vPos,IInteractCenter* pIntractCenter):m_pInteractCenter(pIntractCenter), m_fElapsedTime(0.0f)
{
	m_vPosition = vPos;
	Setup();
	g_EventManager->Attach(eEvent::ReadyBoard, this);
}

CUIReady::~CUIReady()
{
}

void CUIReady::Setup()
{
	CUI* board = new CUIReadyBoard(m_vPosition);
	AddChild(board);
}

bool CUIReady::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::ReadyBoard:
	{
		InvertActive();
		g_EventManager->Attach(eEvent::Tick, this);
	}
		break;
	case eEvent::Tick:
		return TickUpdate(_value);
	}
	return true;
}

bool CUIReady::TickUpdate(void * _value)
{
	ST_TickEvent* data = static_cast<ST_TickEvent*>(_value);
	m_fElapsedTime += data->fElapsedTime;

	if (m_fElapsedTime >= 2.5f)
	{
		InvertActive();
		if (m_pInteractCenter->GetStop())
			m_pInteractCenter->ToggleStop();
		return false;
	}
	else if (m_fElapsedTime >= 1.5f)
	{
		SetActiveUIState();
	}
	return true;
}
