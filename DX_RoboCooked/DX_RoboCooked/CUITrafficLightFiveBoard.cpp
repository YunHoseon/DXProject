#include "stdafx.h"
#include "CUITrafficLightFiveBoard.h"
#include "CUITexture.h"


CUITrafficLightFiveBoard::CUITrafficLightFiveBoard()
{
	Setup();
}


CUITrafficLightFiveBoard::~CUITrafficLightFiveBoard()
{
}

void CUITrafficLightFiveBoard::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/clearChecker_blank_5.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	SetPosition();
	m_pTexture = new CUITexture("data/UI/clearChecker_blank_5.png", NULL, NULL, m_vPosition);

	m_vecLightPosition.resize(5);
	m_vecLightPosition[0] = D3DXVECTOR2(m_vPosition.x +110,  m_vPosition.y - 50);
	m_vecLightPosition[1] = D3DXVECTOR2(m_vPosition.x +230, m_vPosition.y - 50);
	m_vecLightPosition[2] = D3DXVECTOR2(m_vPosition.x +350, m_vPosition.y - 50);
	m_vecLightPosition[3] = D3DXVECTOR2(m_vPosition.x +470, m_vPosition.y - 50);
	m_vecLightPosition[4] = D3DXVECTOR2(m_vPosition.x +590, m_vPosition.y - 50);

}
