#include "stdafx.h"
#include "CUITrafficLightOneBoard.h"
#include "CUITexture.h"


CUITrafficLightOne::CUITrafficLightOne()
{
	Setup();
	SetPosition();
	m_vecLightPosition.resize(1);
}


CUITrafficLightOne::~CUITrafficLightOne()
{
}

void CUITrafficLightOne::Setup()
{
	m_pTexture = new CUITexture("data/UI/clearChecker_blank_1.png", NULL, NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/clearChecker_blank_1.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

	m_vecLightPosition[0] = D3DXVECTOR2(m_vPosition.x + 50, m_vPosition.y + 50);
}						
