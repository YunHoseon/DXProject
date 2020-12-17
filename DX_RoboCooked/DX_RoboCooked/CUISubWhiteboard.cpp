#include "stdafx.h"
#include "CUISubWhiteboard.h"
#include "CUITexture.h"

CUISubWhiteboard::CUISubWhiteboard(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	m_isActive = true;
	Setup();
}


CUISubWhiteboard::~CUISubWhiteboard()
{
}

void CUISubWhiteboard::Setup()
{
	m_pTexture = new CUITexture("data/UI/popUp_Board.png", NULL, NULL, m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/popUp_Board.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
