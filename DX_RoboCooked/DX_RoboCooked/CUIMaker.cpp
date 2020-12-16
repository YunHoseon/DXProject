#include "stdafx.h"
#include "CUIMaker.h"
#include "CUIMakerBoard.h"
#include "CUICloseButton.h"


CUIMaker::CUIMaker()
{
	Setup();

	g_EventManager->Attach(eEvent::MakerClose, this);

	/*g_EventManager->Attach(eEvent::MouseClick, this);
	g_EventManager->Attach(eEvent::MouseHover, this);
	g_EventManager->Attach(eEvent::MouseRelease, this);*/
}


CUIMaker::~CUIMaker()
{
}

void CUIMaker::Setup()
{
	CUI* board = new CUIMakerBoard();
	AddChild(board);
	m_vPosition = board->GetPosition();

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
		break;
	}
	return true;
}
