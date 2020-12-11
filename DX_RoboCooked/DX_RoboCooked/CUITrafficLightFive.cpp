#include "stdafx.h"
#include "CUITrafficLightFive.h"
#include "CUITexture.h"


CUITrafficLightFive::CUITrafficLightFive()
{
	Setup();
	SetPosition();
	m_vecLightPosition.resize(5);

}


CUITrafficLightFive::~CUITrafficLightFive()
{
}

void CUITrafficLightFive::Setup()
{
	m_pTexture = new CUITexture("data/UI/clearChecker_blank_5.png", NULL, NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/clearChecker_blank_5.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

	//lightPosition
	m_vecLightPosition[0] = D3DXVECTOR2(0, 0);
	m_vecLightPosition[1] = D3DXVECTOR2(0, 0);
	m_vecLightPosition[2] = D3DXVECTOR2(0, 0);
	m_vecLightPosition[3] = D3DXVECTOR2(0, 0);
	m_vecLightPosition[4] = D3DXVECTOR2(0, 0);


}
