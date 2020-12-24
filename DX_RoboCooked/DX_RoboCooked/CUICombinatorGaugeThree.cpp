#include "stdafx.h"
#include "CUICombinatorGaugeThree.h"
#include "CUITexture.h"


CUICombinatorGaugeThree::CUICombinatorGaugeThree(D3DXVECTOR3* pPos) :CUIChargeBoard(pPos)
{
	Setup();
}


CUICombinatorGaugeThree::~CUICombinatorGaugeThree()
{
}

void CUICombinatorGaugeThree::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_combine3.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_combine3.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
