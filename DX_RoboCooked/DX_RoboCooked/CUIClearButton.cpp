#include "stdafx.h"
#include "CUIText.h"
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

CUIClearButton::CUIClearButton(D3DXVECTOR2 vPos, IInteractCenter* pInteractCenter) :m_pUIStar(nullptr), m_nTime(0),CUIButton(pInteractCenter)
{
	m_vPosition = vPos;

	//g_EventManager->Attach(eEvent::MouseClick, this);
	//g_EventManager->Attach(eEvent::MouseHover, this);
	//g_EventManager->Attach(eEvent::MouseRelease, this);

	g_EventManager->Attach(eEvent::ClearMain, this);
	g_EventManager->Attach(eEvent::ClearNextStage, this);
	g_EventManager->Attach(eEvent::ClearSetTime, this);
}

CUIClearButton::~CUIClearButton()
{
}

void CUIClearButton::Setup()
{
	D3DXVECTOR2 starPos = m_vPosition;
	starPos.x += 285;
	starPos.y += 150;

	if (m_nTime >= 180)		m_pUIStar = new CUIStarThree(starPos);
	else if (m_nTime >= 120)m_pUIStar = new CUIStarTwo(starPos);
	else if (m_nTime >= 60)	m_pUIStar = new CUIStarOne(starPos);
	else					m_pUIStar = new CUIStarZero(starPos);


	string sTime = CalMin(m_nTime) + ":" + CalSec(m_nTime);

	CUI* board = new CUIClearBoard(D3DXVECTOR2(m_vPosition.x, m_vPosition.y));
	AddChild(board);

	board->AddChild(m_pUIStar);

	CUI* clearTextUI = new CUIClearTime(D3DXVECTOR2(m_vPosition.x + 335, m_vPosition.y + 300) , D3DXVECTOR2(m_vPosition.x + 350, m_vPosition.y + 400) , sTime, eTextType::ClearText);
	board->AddChild(clearTextUI);

	CUI* startBtn = new CUIStartButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 525), eBtnEvent::ClearNextStage);
	board->AddChild(startBtn);

	CUI* mainBtn = new CUIMainButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 525), eBtnEvent::ClearMain);
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
		GoToMain();
		break;
	case eEvent::ClearNextStage:
		NextStage();
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
