#include "stdafx.h"
#include "CUIMainControllButton.h"
#include "CUITexture.h"


CUIMainControllButton::CUIMainControllButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}


CUIMainControllButton::~CUIMainControllButton()
{
}

void CUIMainControllButton::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Main/mainBtn_controll.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	m_vPosition.x -= (m_vSize.x / 2);

	m_pTexture = new CUITexture("data/UI/Main/mainBtn_controll.png", "data/UI/Main/mainBtn_controll_dark.png", "data/UI/Main/mainBtn_controll_light.png", m_vPosition);

}
