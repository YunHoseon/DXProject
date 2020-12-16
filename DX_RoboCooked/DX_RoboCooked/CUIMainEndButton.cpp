#include "stdafx.h"
#include "CUIMainEndButton.h"
#include "CUITexture.h"


CUIMainEndButton::CUIMainEndButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}


CUIMainEndButton::~CUIMainEndButton()
{
}

void CUIMainEndButton::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Main/mainBtn_End.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	m_vPosition.x -= (m_vSize.x / 2);

	m_pTexture = new CUITexture("data/UI/Main/mainBtn_End.png", "data/UI/Main/mainBtn_End_dark.png", "data/UI/Main/mainBtn_End_light.png", m_vPosition);

}
