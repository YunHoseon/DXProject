#include "stdafx.h"
#include "CUIStartButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"

CUIStartButton::CUIStartButton(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIStartButton::~CUIStartButton()
{
}

void CUIStartButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/btn_Start.png", "data/UI/btn_Start_dark.png", "data/UI/btn_Start_light.png", m_vPosition);
	
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/btn_Start.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
