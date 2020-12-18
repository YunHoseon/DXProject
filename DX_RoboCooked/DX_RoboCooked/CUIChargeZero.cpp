#include "stdafx.h"
#include "CUIChargeZero.h"
#include "CUITexture.h"



CUIChargeZero::CUIChargeZero(D3DXVECTOR3* pPos) : CUIChargeBoard(pPos)
{
	Setup();
}


CUIChargeZero::~CUIChargeZero()
{
}

void CUIChargeZero::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_blank.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_blank.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
