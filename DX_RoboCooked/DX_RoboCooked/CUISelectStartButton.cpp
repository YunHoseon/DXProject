#include "stdafx.h"
#include "CUISelectStartButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"

CUISelectStartButton::CUISelectStartButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}


CUISelectStartButton::~CUISelectStartButton()
{
}

void CUISelectStartButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/Stage/select_Start.png", "data/UI/Stage/select_Start_dark.png", "data/UI/Stage/select_Start_light.png", m_vPosition);
	
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_Start.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
