#include "stdafx.h"
#include "CUICloseButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"

CUICloseButton::CUICloseButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}

CUICloseButton::~CUICloseButton()
{
}

void CUICloseButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/btn_Close.png", "data/UI/btn_Close_dark.png", "data/UI/btn_Close_light.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/btn_Close.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
