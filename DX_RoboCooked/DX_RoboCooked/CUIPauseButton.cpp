#include "stdafx.h"
#include "CUIPauseButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"
#include "CUIBoardButton.h"
#include "CUIBarButton.h"
#include "CUICloseButton.h"




CUIPauseButton::CUIPauseButton(D3DXVECTOR2 vPos, WPARAM wParam)
{
	m_vPosition = vPos;
	m_wActiveButton = wParam;
}


CUIPauseButton::~CUIPauseButton()
{
}

void CUIPauseButton::Setup()
{
	g_EventManager->Attach(eEvent::MouseClick, this);
	g_EventManager->Attach(eEvent::MouseHover, this);
	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::MouseRelease, this);


	CUI* board = new CUIBoardButton(D3DXVECTOR2(m_vPosition.x, m_vPosition.y));
	Add(board);

	CUI* close = new CUICloseButton(D3DXVECTOR2(m_vPosition.x + 400, m_vPosition.y+80));
	board->Add(close);

	CUI* bar = new CUIBarButton(D3DXVECTOR2(m_vPosition.x+130, m_vPosition.y+300));
	board->Add(bar);

	bar = new CUIBarButton(D3DXVECTOR2(m_vPosition.x+130, m_vPosition.y+370));
	board->Add(bar);
}

void CUIPauseButton::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::MouseClick:
		ClickEvent(_value);
		break;
	case eEvent::MouseHover:
		HoverEvent(_value);
		break;
	case eEvent::KeyPress:
		KeyPressEvent(_value);
		break;
	case eEvent::MouseRelease:
		MouseReleaseEvent(_value);
		break;
	}
}


void CUIPauseButton::HoverEvent(void* _value)
{
	ST_MouseEvent *data = static_cast<ST_MouseEvent*>(_value);

	for (auto it : m_listUIchildren)
	{
		it->CheckInHover(data->pt);
	}
}

void CUIPauseButton::KeyPressEvent(void * _value)
{
	ST_KeyInputEvent *data = static_cast<ST_KeyInputEvent*>(_value);

	if (data->wKey == m_wActiveButton)
	{
		for (auto it : m_listUIchildren)
		{
			it->InvertActive();
		}
		m_isActive = !m_isActive;

		if (m_isActive)
		{
			g_EventManager->Attach(eEvent::MouseClick, this);
			g_EventManager->Attach(eEvent::MouseHover, this);
		}
		else
		{
			g_EventManager->Detach(eEvent::MouseClick, this);
			g_EventManager->Detach(eEvent::MouseHover, this);
		}
	}
}

void CUIPauseButton::ClickEvent(void* _value)
{
	ST_MouseEvent *data = static_cast<ST_MouseEvent*>(_value);

	for (auto it : m_listUIchildren)
	{
		it->CheckPressIn(data->pt);
	}
}

void CUIPauseButton::MouseReleaseEvent(void * _value)
{
	ST_MouseEvent *data = static_cast<ST_MouseEvent*>(_value);

	for (auto it : m_listUIchildren)
	{
		it->CheckReleaseIn(data->pt);
	}
}
