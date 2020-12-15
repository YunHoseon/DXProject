#include "stdafx.h"
#include "CUIText.h"


CUIText::CUIText(char* ptext, D3DXVECTOR2 vPos)
{
	m_sText = ptext;
	SetRect(&m_rcText, vPos.x, vPos.y,500 , 200);
}


CUIText::~CUIText()
{
}

void CUIText::Update()
{

}

void CUIText::Render()
{
	LPD3DXFONT pFont = g_pFontManager->GetFont(g_pFontManager->CLEARTIME);
	pFont->DrawTextA(NULL,
		m_sText.c_str(),
		m_sText.length(),
		&m_rcText,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));
}
