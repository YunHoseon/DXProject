#include "stdafx.h"
#include "CUITrafficLightThreeBoard.h"
#include "CUITexture.h"


CUITrafficLightThreeBoard::CUITrafficLightThreeBoard()
{
	Setup();
}


CUITrafficLightThreeBoard::~CUITrafficLightThreeBoard()
{
}

void CUITrafficLightThreeBoard::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/clearChecker_blank_3.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	SetPosition();
	m_pTexture = new CUITexture("data/UI/clearChecker_blank_3.png", NULL, NULL, m_vPosition);

	m_vecLightPosition.resize(3);
	m_vecLightPosition[0] = D3DXVECTOR2(m_vPosition.x + 30,  m_vPosition.y - 50);
	m_vecLightPosition[1] = D3DXVECTOR2(m_vPosition.x + 150, m_vPosition.y - 50);
	m_vecLightPosition[2] = D3DXVECTOR2(m_vPosition.x + 270, m_vPosition.y - 50);

}					
