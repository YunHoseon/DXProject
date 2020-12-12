#include "stdafx.h"
#include "CUILight.h"
#include "CUITexture.h"


CUILight::CUILight(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUILight::~CUILight()
{
}

void CUILight::Setup()
{
	m_pTexture = new CUITexture("data/UI/signal_OFF.png", "data/UI/signal_ON.png", NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/signal_OFF.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
