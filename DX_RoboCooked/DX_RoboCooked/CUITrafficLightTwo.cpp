#include "stdafx.h"
#include "CUITrafficLightTwo.h"
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
	m_pTexture = new CUITexture("data/UI/btn_Close.png", "data/UI/btn_Close_dark.png", "data/UI/btn_Close_light.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/btn_Close.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

	m_vecLightPosition[0] = D3DXVECTOR2(0, 0);
	m_vecLightPosition[1] = D3DXVECTOR2(0, 0);

}
