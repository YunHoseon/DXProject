#include "stdafx.h"
#include "CUIReadyBoard.h"
#include "CUITexture.h"


CUIReadyBoard::CUIReadyBoard(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIReadyBoard::~CUIReadyBoard()
{
}

void CUIReadyBoard::Setup()
{
	m_pTexture = new CUITexture("data/UI/prepare_ready.png", "data/UI/prepare_start.png", NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/prepare_ready.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
