#include "stdafx.h"
#include "CUICombinatorGaugeOne.h"
#include "CUITexture.h"


CUICombinatorGaugeOne::CUICombinatorGaugeOne(D3DXVECTOR3* pPos) :CUICombinatorGaugeBoard(pPos)
{
	Setup();
}


CUICombinatorGaugeOne::~CUICombinatorGaugeOne()
{
}

void CUICombinatorGaugeOne::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_charge1.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_charge1.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
