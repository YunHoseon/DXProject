#include "stdafx.h"
#include "CUISelectMainButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"

CUISelectMainButton::CUISelectMainButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();

}

CUISelectMainButton::~CUISelectMainButton()
{
}

void CUISelectMainButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/Stage/select_Main.png", "data/UI/Stage/select_Main_dark.png", "data/UI/Stage/select_Main_light.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_Main.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
