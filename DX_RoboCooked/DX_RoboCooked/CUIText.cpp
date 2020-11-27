#include "stdafx.h"
#include "CUIText.h"


CUIText::CUIText(char* ptext, D3DXVECTOR2 vPos)
{
	m_sText = ptext;
	m_vPosition = vPos;
	SetRect(&m_rcText, vPos.x, vPos.y, 500, 200);
}


CUIText::~CUIText()
{
}

void CUIText::Update()
{
	D3DXMATRIXA16 matS, matT, matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, 0);

	m_matWorld = matS * matR * matT;
	if (m_pParentWorldTM)
		m_matWorld *= *m_pParentWorldTM;
}

void CUIText::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD,&m_matWorld);
	LPD3DXFONT pFont = g_pFontManager->GetFont(g_pFontManager->DEFAULT);

	pFont->DrawTextA(NULL,
		m_sText.c_str(),
		m_sText.length(),
		&m_rcText,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));

}
