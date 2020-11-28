#include "stdafx.h"
#include "CUIPauseButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"
#include "CUIBoardButton.h"
#include "CUIBarButton.h"
#include "CUICloseButton.h"




CUIPauseButton::CUIPauseButton(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
}


CUIPauseButton::~CUIPauseButton()
{
}

void CUIPauseButton::Setup()
{
	g_EventManager->Attach(eEvent::MouseClick, this);
	g_EventManager->Attach(eEvent::MouseHover, this);


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
	}



}

void CUIPauseButton::ClickEvent(void* _value)
{
	
	ST_MouseEvent *data = static_cast<ST_MouseEvent*>(_value);

	for (auto it : m_listUIchildren)
	{
		it->CheckIn(data->pt);
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
