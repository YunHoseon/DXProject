#include "stdafx.h"
#include "CUIControll.h"
#include "CUIControllBoard.h"
#include "CUICloseButton.h"


CUIControll::CUIControll(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();

	g_EventManager->Attach(eEvent::ControllClose, this);
}


CUIControll::~CUIControll()
{
	
}

void CUIControll::Setup()
{
	CUIButton* board = new CUIControllBoard(m_vPosition);
	AddChild(board);

	CUIButton* closeUI = new CUICloseButton(D3DXVECTOR2(m_vPosition.x + 450 , m_vPosition.y + 650), eBtnEvent::ControllClose);
	board->AddChild(closeUI);
}

bool CUIControll::OnEvent(eEvent eEvent, void * _value)
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
	case eEvent::ControllClose:
		ActiveUI();
		break;
	}
	return true;
}
