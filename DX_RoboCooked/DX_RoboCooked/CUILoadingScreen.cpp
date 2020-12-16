#include "stdafx.h"
#include "CUILoadingScreen.h"
#include "CUITexture.h"

CUILoadingScreen::CUILoadingScreen()
{
	m_vPosition = D3DXVECTOR2(0, 0);
	m_isActive = true;
	Setup();
}


CUILoadingScreen::~CUILoadingScreen()
{
}

void CUILoadingScreen::Setup()
{
	m_pTexture = new CUITexture("data/UI/roadingScreen.png", NULL, NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/roadingScreen.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
