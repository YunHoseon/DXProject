#include "stdafx.h"
#include "CUIMainMakerButton.h"
#include "CUITexture.h"


CUIMainMakerButton::CUIMainMakerButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}


CUIMainMakerButton::~CUIMainMakerButton()
{
}

void CUIMainMakerButton::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Main/mainBtn_maker.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	m_vPosition.x -= (m_vSize.x / 2);

	m_pTexture = new CUITexture("data/UI/Main/mainBtn_maker.png", "data/UI/Main/mainBtn_maker_dark.png", "data/UI/Main/mainBtn_maker_light.png", m_vPosition);
}
