#include "stdafx.h"
#include "CUITipBoardText.h"
#include "CUIText.h"


CUITipBoardText::CUITipBoardText(D3DXVECTOR2 vPos, string sText, int nWidth, int nHeight):m_sTipText(sText), m_nWidth(nWidth), m_nHeight(nHeight)
{
	m_vPosition = vPos;
	Setup();
}


CUITipBoardText::~CUITipBoardText()
{
}

void CUITipBoardText::Setup()
{
	m_pText = new CUIText(m_sTipText,m_vPosition, m_nWidth, m_nHeight);
}
