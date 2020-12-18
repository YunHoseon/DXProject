#include "stdafx.h"
#include "CUIChargeThree.h"
#include "CUITexture.h"



CUIChargeThree::CUIChargeThree(D3DXVECTOR3* pPos) : CUIChargeBoard(pPos)
{
	Setup();
}


CUIChargeThree::~CUIChargeThree()
{
}

void CUIChargeThree::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_charge3.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_charge3.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
