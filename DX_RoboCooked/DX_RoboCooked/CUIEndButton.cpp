#include "stdafx.h"
#include "CUIEndButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"


CUIEndButton::CUIEndButton(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}

CUIEndButton::~CUIEndButton()
{
}

void CUIEndButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/btn_End.png", "data/UI/btn_End_dark.png", "data/UI/btn_End_light.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/btn_End.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
