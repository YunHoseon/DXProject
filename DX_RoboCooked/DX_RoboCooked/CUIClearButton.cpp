#include "stdafx.h"
#include "CUIClearButton.h"
#include "CUIClearBoard.h"
#include "CUIStar.h"
#include "CUIStarZero.h"
#include "CUIStarOne.h"
#include "CUIStarTwo.h"
#include "CUIStarThree.h"
#include "CUIClearTime.h"
#include "CUIMainButton.h"
#include "CUIStartButton.h"

CUIClearButton::CUIClearButton(IInteractCenter* pInteractCenter):m_pUIStar(nullptr), m_nTime(0)
{
	m_pInteractCenter = pInteractCenter;
	g_EventManager->Attach(eEvent::ClearMain, this);
	g_EventManager->Attach(eEvent::ClearNextStage, this);
	g_EventManager->Attach(eEvent::ClearSetTime, this);
}

CUIClearButton::~CUIClearButton()
{
}

void CUIClearButton::Setup()
{
	string sTime = m_pInteractCenter->CalMin(m_nTime) + ":" + m_pInteractCenter->CalSec(m_nTime);

	CUI* board = new CUIClearBoard(sTime, eBtnEvent::None);
	AddChild(board);

	m_vPosition = board->GetPosition();


	D3DXVECTOR2 starPos = m_vPosition;
	starPos.x += 285;
	starPos.y += 150;

	if (m_nTime >= 180)		m_pUIStar = new CUIStarThree(starPos);
	else if (m_nTime >= 120)m_pUIStar = new CUIStarTwo(starPos);
	else if (m_nTime >= 60)	m_pUIStar = new CUIStarOne(starPos);
	else					m_pUIStar = new CUIStarZero(starPos);


	
	board->AddChild(m_pUIStar);

	CUI* clearTextUI = new CUIClearTime(D3DXVECTOR2(m_vPosition.x + 335, m_vPosition.y + 300), eBtnEvent::None);
	board->AddChild(clearTextUI);
	
	CUI* startBtn = new CUIStartButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 525), eBtnEvent::PauseReset);
	board->AddChild(startBtn);

	CUI* mainBtn = new CUIMainButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 525), eBtnEvent::PauseMain);
	board->AddChild(mainBtn);
}

bool CUIClearButton::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::MouseClick:
		MouseClickEvent(_value);
		break;
	case eEvent::MouseHover:
		MouseHoverEvent(_value);
		break;
	case eEvent::MouseRelease:
	{
		MouseReleaseEvent(_value);
		return m_isActive;
	}
		break;
	case eEvent::ClearMain:
		break;
	case eEvent::ClearNextStage:
		break;
	case eEvent::ClearSetTime:
		SetTimeEvent(_value);
		break;
	}

	return true;
}

void CUIClearButton::SetTimeEvent(void * _value)
{
	ST_SetTimeEvent* data = static_cast<ST_SetTimeEvent*>(_value);
	m_nTime = data->nTime;
	Setup();
}
