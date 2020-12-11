#include "stdafx.h"
#include "CUIMainButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"


CUIMainButton::CUIMainButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
	
}

CUIMainButton::~CUIMainButton()
{
}

void CUIMainButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/btn_Main.png", "data/UI/btn_Main_dark.png", "data/UI/btn_Main_light.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/btn_Main.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
