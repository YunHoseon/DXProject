#include "stdafx.h"
#include "CUITrafficLightTwoBoard.h"
#include "CUITexture.h"


CUITrafficLightTwo::CUITrafficLightTwo()
{
	Setup();
	SetPosition();
	m_vecLightPosition.resize(2);
}


CUITrafficLightTwo::~CUITrafficLightTwo()
{
}

void CUITrafficLightTwo::Setup()
{
	m_pTexture = new CUITexture("data/UI/clearChecker_blank_2.png", NULL, NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/clearChecker_blank_2.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

	m_vecLightPosition[0] = D3DXVECTOR2(m_vPosition.x + 50, m_vPosition.y + 50);
	m_vecLightPosition[1] = D3DXVECTOR2(m_vPosition.x + 150, m_vPosition.y + 50);
}			