#include "stdafx.h"
#include "CUIChargeTwo.h"
#include "CUITexture.h"



CUIChargeTwo::CUIChargeTwo(D3DXVECTOR3* pPos) : CUIChargeBoard(pPos)
{
	Setup();
}


CUIChargeTwo::~CUIChargeTwo()
{
}

void CUIChargeTwo::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_combine2.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_combine2.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
