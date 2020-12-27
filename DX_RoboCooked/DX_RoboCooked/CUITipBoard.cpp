#include "stdafx.h"
#include "CUITipBoard.h"
#include "CUIPopUpBoard.h"
#include "CUITipBoardText.h"

CUITipBoard::CUITipBoard(D3DXVECTOR2 vPos):m_pPopUpBoard(nullptr)
{
	m_vPosition = vPos;
	Setup();
}


CUITipBoard::~CUITipBoard()
{
}

void CUITipBoard::Setup()
{
	m_pPopUpBoard = new CUIPopUpBoard(m_vPosition);
	AddChild(m_pPopUpBoard);

}

void CUITipBoard::SetText(string sText, int nWidth, int nHeight)
{
	 CUI* text = new CUITipBoardText(D3DXVECTOR2(m_vPosition.x + 90,m_vPosition.y + 150), sText,nWidth,nHeight);
	 m_pPopUpBoard->AddChild(text);
}
