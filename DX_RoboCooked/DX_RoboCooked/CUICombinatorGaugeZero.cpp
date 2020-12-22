#include "stdafx.h"
#include "CUICombinatorGaugeZero.h"
#include "CUITexture.h"

CUICombinatorGaugeZero::CUICombinatorGaugeZero(D3DXVECTOR3* pPos) :CUICombinatorGaugeBoard(pPos)
{
	Setup();
}


CUICombinatorGaugeZero::~CUICombinatorGaugeZero()
{
}

void CUICombinatorGaugeZero::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_blank.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_blank.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
