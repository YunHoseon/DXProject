#include "stdafx.h"
#include "CUIMakerBoard.h"
#include "CUITexture.h"


CUIMakerBoard::CUIMakerBoard(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIMakerBoard::~CUIMakerBoard()
{
}

void CUIMakerBoard::Setup()
{
	m_pTexture = new CUITexture("data/UI/Main/popUp_maker_fill.png", NULL, NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Main/popUp_maker_fill.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
