#include "stdafx.h"
#include "CUIChargeOne.h"
#include "CUITexture.h"



CUIChargeOne::CUIChargeOne(D3DXVECTOR3* pPos) : CUIChargeBoard(pPos)
{
	Setup();
}


CUIChargeOne::~CUIChargeOne()
{
}

void CUIChargeOne::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_combine1.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_combine1.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
