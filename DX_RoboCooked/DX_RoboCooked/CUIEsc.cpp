#include "stdafx.h"
#include "CUIEsc.h"
#include "CUITexture.h"


CUIEsc::CUIEsc()
{
	Setup();
}


CUIEsc::~CUIEsc()
{
}

void CUIEsc::Setup()
{
	m_pTexture = new CUITexture("data/UI/button_esc.png", "data/UI/button_esc_dark.png", "data/UI/button_esc_light.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/button_esc.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

	SetActive(true);
}
