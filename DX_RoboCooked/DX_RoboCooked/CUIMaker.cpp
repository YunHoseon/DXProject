#include "stdafx.h"
#include "CUIMaker.h"
#include "CUIMakerBoard.h"
#include "CUICloseButton.h"


CUIMaker::CUIMaker(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();

	g_EventManager->Attach(eEvent::MakerClose, this);
}


CUIMaker::~CUIMaker()
{
}

void CUIMaker::Setup()
{
	CUI* board = new CUIMakerBoard(m_vPosition);
	AddChild(board);

	CUI* closeUI = new CUICloseButton(D3DXVECTOR2(m_vPosition.x + 450, m_vPosition.y + 650), eBtnEvent::MakerClose);
	board->AddChild(closeUI);
}

bool CUIMaker::OnEvent(eEvent eEvent, void * _value)
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
	case eEvent::MakerClose:
		ActiveUI();
		g_EventManager->CallEvent(eEvent::MainEvent, NULL);
		break;
	}
	return true;
}
