#include "stdafx.h"
#include "CUIMainScreenBoard.h"
#include "CUITexture.h"


CUIMainScreenBoard::CUIMainScreenBoard()
{
	Setup();
}


CUIMainScreenBoard::~CUIMainScreenBoard()
{
}

void CUIMainScreenBoard::Setup()
{
	m_pTexture = new CUITexture("data/UI/Main/mainScreen.png", NULL, NULL, m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Main/mainScreen.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
