#include "stdafx.h"
#include "CUICombinatorGaugeTwo.h"
#include "CUITexture.h"


CUICombinatorGaugeTwo::CUICombinatorGaugeTwo(D3DXVECTOR3* pPos) :CUICombinatorGaugeBoard(pPos)
{
	Setup();
}


CUICombinatorGaugeTwo::~CUICombinatorGaugeTwo()
{
}

void CUICombinatorGaugeTwo::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_charge2.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_charge2.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
