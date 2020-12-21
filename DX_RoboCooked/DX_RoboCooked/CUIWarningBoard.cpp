#include "stdafx.h"
#include "CUIWarningBoard.h"
#include "CUITexture.h"
//D3DXVECTOR2(0,-150)
CUIWarningBoard::CUIWarningBoard(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIWarningBoard::~CUIWarningBoard()
{
}

void CUIWarningBoard::Setup()
{
	m_pTexture = new CUITexture("data/UI/warning.png", NULL, NULL,m_vPosition,eUIState::invisible);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/warning.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
