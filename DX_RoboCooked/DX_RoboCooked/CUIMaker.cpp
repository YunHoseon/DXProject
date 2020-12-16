#include "stdafx.h"
#include "CUIMaker.h"
#include "CUIMakerBoard.h"
#include "CUICloseButton.h"


CUIMaker::CUIMaker(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();

	g_EventManager->Attach(eEvent::MakerClose, this);

	g_EventManager->Attach(eEvent::MouseClick, this);
	g_EventManager->Attach(eEvent::MouseHover, this);
	g_EventManager->Attach(eEvent::MouseRelease, this);
}


CUIMaker::~CUIMaker()
{
}

void CUIMaker::Setup()
{
	CUI* board = new CUIMakerBoard(m_vPosition);
	Add(board);

	CUI* closeUI = new CUICloseButton(D3DXVECTOR2(m_vPosition.x + 450, m_vPosition.y + 650), eBtnEvent::MakerClose);
	board->Add(closeUI);
}

bool CUIMaker::OnEvent(eEvent eEvent, void * _value)
{
	if (!m_isActive)
		return true;

	switch (eEvent)
	{
	case eEvent::MouseClick:
		MouseClickEvent(_value);
		break;
	case eEvent::MouseHover:
		MouseHoverEvent(_value);
		break;
	case eEvent::MouseRelease:
		MouseReleaseEvent(_value);
		break;
	case eEvent::MakerClose:
		InvertActive();
		break;
	}
	return true;
}
