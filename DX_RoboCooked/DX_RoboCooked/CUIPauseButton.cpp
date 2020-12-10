#include "stdafx.h"
#include "CUIPauseButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"
#include "CUIPauseBoard.h"
#include "CUIResetButton.h"
#include "CUIEndButton.h"
#include "CUIMainButton.h"
#include "CUICloseButton.h"
#include "IInteractCenter.h"



CUIPauseButton::CUIPauseButton(D3DXVECTOR2 vPos, WPARAM wParam, IInteractCenter* pInteractCenter)
{
	m_pInteractCenter = pInteractCenter;
	m_vPosition = vPos;
	m_wActiveButton = wParam;
	Setup();
}


CUIPauseButton::~CUIPauseButton()
{
}

void CUIPauseButton::Setup()
{
	//g_EventManager->Attach(eEvent::MouseClick, this);
	//g_EventManager->Attach(eEvent::MouseHover, this);
	g_EventManager->Attach(eEvent::KeyPress, this);
	g_EventManager->Attach(eEvent::KeyRelease, this);
	g_EventManager->Attach(eEvent::MouseRelease, this);

	CUI* board = new CUIPauseBoard(D3DXVECTOR2(m_vPosition.x, m_vPosition.y));
	Add(board);

	CUI* mainBtn = new CUIMainButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 200));
	board->Add(mainBtn);

	CUI* closeBtn = new CUICloseButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 200));
	board->Add(closeBtn);

	CUI* ResetBtn = new CUIResetButton(D3DXVECTOR2(m_vPosition.x + 250, m_vPosition.y + 500));
	board->Add(ResetBtn);

	CUI* EndBtn = new CUIEndButton(D3DXVECTOR2(m_vPosition.x + 550, m_vPosition.y + 500));
	board->Add(EndBtn);


	

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
	case eEvent::KeyRelease:
		KeyReleaseEvent(_value);
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
		if (m_isKeyDown == false)
		{
			m_isKeyDown = true;

			for (auto it : m_listUIchildren)
			{
				it->InvertActive();
			}
			m_isActive = !m_isActive;

			if (m_isActive)
			{
				g_EventManager->Attach(eEvent::MouseClick, this);
				g_EventManager->Attach(eEvent::MouseHover, this);
				g_EventManager->Attach(eEvent::MouseRelease, this);
			}
			else
			{
				g_EventManager->Detach(eEvent::MouseClick, this);
				g_EventManager->Detach(eEvent::MouseHover, this);
				g_EventManager->Detach(eEvent::MouseRelease, this);
			}
			m_pInteractCenter->ToggleStop();
		}

		
	}
}

void CUIPauseButton::KeyReleaseEvent(void * _value)
{
	ST_KeyInputEvent* data = static_cast<ST_KeyInputEvent*>(_value);
	
	if (data->wKey == m_wActiveButton)
	{
		m_isKeyDown = false;
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
