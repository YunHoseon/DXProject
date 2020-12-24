#include "stdafx.h"
#include "CUICombinatorGaugeFour.h"
#include "CUITexture.h"


CUICombinatorGaugeFour::CUICombinatorGaugeFour(D3DXVECTOR3* pPos) :CUIChargeBoard(pPos)
{
	Setup();
}


CUICombinatorGaugeFour::~CUICombinatorGaugeFour()
{
}

void CUICombinatorGaugeFour::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_combine4.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_combine4.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
