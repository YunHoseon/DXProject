#include "stdafx.h"
#include "CUIText.h"


CUIText::CUIText(string ptext, D3DXVECTOR2 vPos, eTextType type)
{
	m_sText = ptext;
	m_eType = type;
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

	if (m_eType == eTextType::ClearText)
	{
		LPD3DXFONT pFont = g_pFontManager->GetFont(g_pFontManager->CLEARTIME);
		pFont->DrawTextA(NULL,
			m_sText.c_str(),
			m_sText.length(),
			&m_rcText,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (m_eType == eTextType::SelectText)
	{
		LPD3DXFONT pFont = g_pFontManager->GetFont(g_pFontManager->SELECT);
		pFont->DrawTextA(NULL,
			m_sText.c_str(),
			m_sText.length(),
			&m_rcText,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(0, 0, 0));
	}
	else if (m_eType == eTextType::UpdateText)
	{
		LPD3DXFONT pFont = g_pFontManager->GetFont(g_pFontManager->UPDATE);
		pFont->DrawTextA(NULL,
			m_sText.c_str(),
			m_sText.length(),
			&m_rcText,
			DT_LEFT | DT_TOP | DT_NOCLIP,
			D3DCOLOR_XRGB(0, 0, 0));
	}
	
}
