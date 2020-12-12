#include "stdafx.h"
#include "CUITrafficLightTwoBoard.h"
#include "CUITexture.h"


CUITrafficLightTwoBoard::CUITrafficLightTwoBoard()
{
	Setup();
}


CUITrafficLightTwoBoard::~CUITrafficLightTwoBoard()
{
}

void CUITrafficLightTwoBoard::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/clearChecker_blank_2.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	SetPosition();
	m_pTexture = new CUITexture("data/UI/clearChecker_blank_2.png", NULL, NULL, m_vPosition);

	m_vecLightPosition.resize(2);
	m_vecLightPosition[0] = D3DXVECTOR2(m_vPosition.x-20, m_vPosition.y - 50);
	m_vecLightPosition[1] = D3DXVECTOR2(m_vPosition.x + 120, m_vPosition.y -50);
}			