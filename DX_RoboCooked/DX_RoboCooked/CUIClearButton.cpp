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

CUIClearButton::CUIClearButton(D3DXVECTOR2 vPos, FLOAT fTime, IInteractCenter* pInteractCenter):m_pUIStar(nullptr)
{
	m_vPosition = vPos;
	D3DXVECTOR2 starPos = vPos;
	starPos.x += 285;
	starPos.y += 150;

	if (fTime >= 180)		m_pUIStar = new CUIStarThree(starPos);
	else if (fTime >= 120)	m_pUIStar = new CUIStarTwo(starPos);
	else if (fTime >= 60)	m_pUIStar = new CUIStarOne(starPos);
	else					m_pUIStar = new CUIStarZero(starPos);


	Setup();

	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::MouseRelease, this);
	InvertActive();
}

CUIClearButton::~CUIClearButton()
{
}

void CUIClearButton::Setup()
{
	CUI* board = new CUIClearBoard(D3DXVECTOR2(m_vPosition.x, m_vPosition.y), eBtnEvent::None);
	Add(board);

	board->Add(m_pUIStar);

	CUI* clearTextUI = new CUIClearTime(D3DXVECTOR2(m_vPosition.x + 335, m_vPosition.y + 300), eBtnEvent::None);
	board->Add(clearTextUI);
	
	CUI* startBtn = new CUIStartButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 525), eBtnEvent::PauseReset);
	board->Add(startBtn);

	CUI* mainBtn = new CUIMainButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 525), eBtnEvent::PauseMain);
	board->Add(mainBtn);


	
}

void CUIClearButton::OnEvent(eEvent eEvent, void * _value)
{
}

void CUIClearButton::ClickEvent(void * _value)
{
}

void CUIClearButton::HoverEvent(void * _value)
{
}

void CUIClearButton::KeyPressEvent(void * _value)
{
}

void CUIClearButton::KeyReleaseEvent(void * _value)
{
}

void CUIClearButton::MouseReleaseEvent(void * _value)
{
}
