#include "stdafx.h"
#include "CUITryAgain.h"
#include "CUITexture.h"

CUITryAgain::CUITryAgain(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}

CUITryAgain::~CUITryAgain()
{
}

void CUITryAgain::Setup()
{
	m_pTexture = new CUITexture("data/UI/tryAgain.png", "data/UI/tryAgain.png", "data/UI/tryAgain.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/tryAgain.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
