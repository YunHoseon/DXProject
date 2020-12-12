#include "stdafx.h"
#include "CUITrafficLightOneBoard.h"
#include "CUITexture.h"


CUITrafficLightOneBoard::CUITrafficLightOneBoard()
{
	Setup();
}


CUITrafficLightOneBoard::~CUITrafficLightOneBoard()
{
}

void CUITrafficLightOneBoard::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/clearChecker_blank_1.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	SetPosition();
	m_pTexture = new CUITexture("data/UI/clearChecker_blank_1.png", NULL, NULL, m_vPosition);

	m_vecLightPosition.resize(1);
	m_vecLightPosition[0] = D3DXVECTOR2(m_vPosition.x -50, m_vPosition.y - 50);
}						
