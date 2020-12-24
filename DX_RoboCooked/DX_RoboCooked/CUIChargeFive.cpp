#include "stdafx.h"
#include "CUIChargeFive.h"
#include "CUITexture.h"


CUIChargeFive::CUIChargeFive(D3DXVECTOR3* pPos) : CUIChargeBoard(pPos)
{
	Setup();
}


CUIChargeFive::~CUIChargeFive()
{
}

void CUIChargeFive::Setup()
{
	m_pTexture = new CUITexture("data/UI/gauge_combine5.png", NULL, NULL, m_pPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/gauge_combine5.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
