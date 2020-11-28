#include "stdafx.h"
#include "CUICloseButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"


CUICloseButton::CUICloseButton(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUICloseButton::~CUICloseButton()
{
}

void CUICloseButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/btn-main-menu.png", "data/UI/arrow-btn-r-up.png", "data/UI/arrow-btn-r-down.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/btn-main-menu.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

}
