#include "stdafx.h"
#include "CUIText.h"


CUIText::CUIText(char* ptext)
{
	m_sText = ptext;
	
}


CUIText::~CUIText()
{
}

void CUIText::Update()
{

}

void CUIText::Render()
{
	LPD3DXFONT pFont = g_pFontManager->GetFont(g_pFontManager->DEFAULT);
	SetRect(&m_rcText, m_vPosition.x, m_vPosition.y, 500, 200);
	pFont->DrawTextA(NULL,
		m_sText.c_str(),
		m_sText.length(),
		&m_rcText,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));

}
