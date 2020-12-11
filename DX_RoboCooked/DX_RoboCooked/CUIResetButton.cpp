#include "stdafx.h"
#include "CUIResetButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"


CUIResetButton::CUIResetButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}


CUIResetButton::~CUIResetButton()
{
}

void CUIResetButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/btn_Reset.png", "data/UI/btn_Reset_dark.png", "data/UI/btn_Reset_light.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/btn_Reset.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

}
