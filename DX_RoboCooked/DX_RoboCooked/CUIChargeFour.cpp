#include "stdafx.h"
#include "CUIChargeFour.h"
#include "CUITexture.h"



CUIChargeFour::CUIChargeFour(D3DXVECTOR3* pPos) : CUIChargeBoard(pPos)
{
	Setup();
}


CUIChargeFour::~CUIChargeFour()
{
}

void CUIChargeFour::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_charge4.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_charge4.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
