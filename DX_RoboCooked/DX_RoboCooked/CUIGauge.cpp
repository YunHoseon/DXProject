#include "stdafx.h"
#include "CUIGauge.h"
#include "CUITexture.h"


CUIGauge::CUIGauge(D3DXVECTOR3* vPos)
{
	m_pPosition = vPos;
	Setup();
}


CUIGauge::~CUIGauge()
{
}

void CUIGauge::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_inner.png", "data/UI/gauge_inner.png", "data/UI/gauge_inner.png", m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_inner.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
