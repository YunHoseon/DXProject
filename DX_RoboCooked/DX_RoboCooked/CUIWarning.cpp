#include "stdafx.h"
#include "CUIWarning.h"
#include "CUIWarningBoard.h"


CUIWarning::CUIWarning() :m_fElapsedTime(0.0f), m_nRepeatCount(4),m_nBlinkCount(0), m_isBlink(false)
{
	g_EventManager->Attach(eEvent::CallWarning, this);
	Setup();
}


CUIWarning::~CUIWarning()
{
}

void CUIWarning::Setup()
{
	CUI* board = new CUIWarningBoard(D3DXVECTOR2(0, -150));
	AddChild(board);
}

bool CUIWarning::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::Tick:
		return TickUpdate(_value);
		break;
	case eEvent::CallWarning:
	{
		g_SoundManager->PlaySFX("siren");
		g_EventManager->Attach(eEvent::Tick, this);
	}
		break;
	default:
		break;
	}
	return true;
}

bool CUIWarning::TickUpdate(void * _value)
{
	ST_TickEvent* data = static_cast<ST_TickEvent*>(_value);
	m_fElapsedTime += data->fElapsedTime;

	if (m_isBlink && m_fElapsedTime >= 0.5f)
	{
		InvertActive();
		m_isBlink = false;
		m_fElapsedTime = 0;
		m_nBlinkCount++;
		if (m_nBlinkCount == m_nRepeatCount)
		{
			SetActive(false);
			return false;
		}
	}
	else if (!m_isBlink && m_fElapsedTime >= 0.25f)
	{
		m_isBlink = true;
		InvertActive();
	}


	return true;
}
