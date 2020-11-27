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
	CUI* board = new CUIBoardButton(D3DXVECTOR2(m_vPosition.x, m_vPosition.y));
	Add(board);

	CUI* close = new CUICloseButton(D3DXVECTOR2(m_vPosition.x + 400, m_vPosition.y+80));
	board->Add(close);

	CUI* bar = new CUIBarButton(D3DXVECTOR2(m_vPosition.x+130, m_vPosition.y+300));
	board->Add(bar);

	bar = new CUIBarButton(D3DXVECTOR2(m_vPosition.x+130, m_vPosition.y+370));
	board->Add(bar);
}

void CUIPauseButton::Update()
{
	for (const auto c : m_listUIchildren)
	{
		c->Update();
	}
}

void CUIPauseButton::Render()
{
	for (const auto c : m_listUIchildren)
	{
		c->Render();
	}
}
