#include "stdafx.h"
#include "CUITrafficLightFourBoard.h"
#include "CUITexture.h"


CUITrafficLightFourBoard::CUITrafficLightFourBoard()
{
	Setup();
}


CUITrafficLightFourBoard::~CUITrafficLightFourBoard()
{
}

void CUITrafficLightFourBoard::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/clearChecker_blank_4.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	SetPosition();
	m_pTexture = new CUITexture("data/UI/clearChecker_blank_4.png", NULL, NULL, m_vPosition);

	m_vecLightPosition.resize(4);
	m_vecLightPosition[0] = D3DXVECTOR2(m_vPosition.x + 60,  m_vPosition.y - 50);
	m_vecLightPosition[1] = D3DXVECTOR2(m_vPosition.x + 180, m_vPosition.y - 50);
	m_vecLightPosition[2] = D3DXVECTOR2(m_vPosition.x + 300, m_vPosition.y - 50);
	m_vecLightPosition[3] = D3DXVECTOR2(m_vPosition.x + 420, m_vPosition.y - 50);

}
