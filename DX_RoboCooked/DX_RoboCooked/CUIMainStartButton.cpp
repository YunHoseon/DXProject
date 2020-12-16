#include "stdafx.h"
#include "CUIMainStartButton.h"
#include "CUITexture.h"


CUIMainStartButton::CUIMainStartButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}

CUIMainStartButton::~CUIMainStartButton()
{
}

void CUIMainStartButton::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Main/mainBtn_start.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	m_vPosition.x -= (m_vSize.x / 2);

	m_pTexture = new CUITexture("data/UI/Main/mainBtn_start.png", "data/UI/Main/mainBtn_start_dark.png", "data/UI/Main/mainBtn_start_light.png", m_vPosition);

}
