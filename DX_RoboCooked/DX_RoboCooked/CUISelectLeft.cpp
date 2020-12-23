#include "stdafx.h"
#include "CUISelectLeft.h"
#include "CUITexture.h"

CUISelectLeft::CUISelectLeft(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}


CUISelectLeft::~CUISelectLeft()
{
}

void CUISelectLeft::Setup()
{
	m_pTexture = new CUITexture("data/UI/Stage/select_left.png", "data/UI/Stage/select_left_dark.png", "data/UI/Stage/select_left_light.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_left.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
