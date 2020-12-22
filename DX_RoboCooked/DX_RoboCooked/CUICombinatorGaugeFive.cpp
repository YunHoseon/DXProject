#include "stdafx.h"
#include "CUICombinatorGaugeFive.h"
#include "CUITexture.h"


CUICombinatorGaugeFive::CUICombinatorGaugeFive(D3DXVECTOR3* pPos):CUICombinatorGaugeBoard(pPos)
{
	Setup();
}


CUICombinatorGaugeFive::~CUICombinatorGaugeFive()
{
}

void CUICombinatorGaugeFive::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_charge5.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_charge5.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
