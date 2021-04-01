#include "stdafx.h"
#include "CGameScene.h"
#include "CUILoseButton.h"
#include "CUILoseBoard.h"
#include "CUIStarZero.h"
#include "CUITryAgain.h"
#include "CUIMainButton.h"
#include "CUIResetButton.h"
#include "IInteractCenter.h"


CUILoseButton::CUILoseButton(D3DXVECTOR2 vPos, IInteractCenter* pInteractCenter) :CUIButton(pInteractCenter)
{
	m_vPosition = vPos;
	Setup();

	g_EventManager->Attach(eEvent::LoseMain, this);
	g_EventManager->Attach(eEvent::LoseReset, this);
}


CUILoseButton::~CUILoseButton()
{
}

void CUILoseButton::Setup()
{
	CUI* board = new CUILoseBoard(D3DXVECTOR2(m_vPosition.x, m_vPosition.y));
	AddChild(board);

	CUI* starUI = new CUIStarZero(D3DXVECTOR2(m_vPosition.x + 285, m_vPosition.y + 150));
	board->AddChild(starUI);

	CUI* tryAgainUI = new CUITryAgain(D3DXVECTOR2(m_vPosition.x + 320, m_vPosition.y + 350));
	board->AddChild(tryAgainUI);

	CUI* mainBtn = new CUIMainButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 500), eBtnEvent::LoseMain);
	board->AddChild(mainBtn);

	CUI* ResetBtn = new CUIResetButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 500), eBtnEvent::LoseReset);
	board->AddChild(ResetBtn);

}

bool CUILoseButton::OnEvent(eEvent eEvent, void * _value)
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
	case eEvent::LoseMain:
		GoToMain();
		break;
	case eEvent::LoseReset:
		ResetGame();
		break;
	}
	return true;
}
