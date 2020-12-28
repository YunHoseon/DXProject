#include "stdafx.h"
#include "CUITipBoardText.h"
#include "CUIText.h"


CUITipBoardText::CUITipBoardText(D3DXVECTOR2 vPos, string sText, int nWidth, int nHeight):m_sTipText(sText), m_nWidth(nWidth), m_nHeight(nHeight), m_wsTipText(L"")
{
	m_vPosition = vPos;
	Setup();
}

CUITipBoardText::CUITipBoardText(D3DXVECTOR2 vPos, std::wstring wsText, int nWidth, int nHeight):m_sTipText(""), m_nWidth(nWidth), m_nHeight(nHeight), m_wsTipText(wsText)
{
	m_vPosition = vPos;
	m_pText = new CUIText(m_wsTipText, m_vPosition, m_nWidth, m_nHeight, eTextType::TipText);
}


CUITipBoardText::~CUITipBoardText()
{
}

void CUITipBoardText::Setup()
{
	m_pText = new CUIText(m_sTipText,m_vPosition, m_nWidth, m_nHeight, eTextType::TipText);
}
