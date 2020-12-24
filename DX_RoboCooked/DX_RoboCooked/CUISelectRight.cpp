#include "stdafx.h"
#include "CUISelectRight.h"
#include "CUITexture.h"


CUISelectRight::CUISelectRight(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}


CUISelectRight::~CUISelectRight()
{
}

void CUISelectRight::Setup()
{
	m_pTexture = new CUITexture("data/UI/Stage/select_right.png", "data/UI/Stage/select_right_dark.png", "data/UI/Stage/select_right_light.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_right.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
