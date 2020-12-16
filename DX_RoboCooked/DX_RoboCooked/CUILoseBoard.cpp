#include "stdafx.h"
#include "CUILoseBoard.h"
#include "CUITexture.h"


CUILoseBoard::CUILoseBoard(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUILoseBoard::~CUILoseBoard()
{
}

void CUILoseBoard::Setup()
{
	m_pTexture = new CUITexture("data/UI/popUp_lose.png", NULL, NULL, m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/popUp_lose.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
