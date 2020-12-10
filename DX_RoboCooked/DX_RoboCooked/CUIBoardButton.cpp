#include "stdafx.h"
#include "CUIBoardButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"


CUIBoardButton::CUIBoardButton(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIBoardButton::~CUIBoardButton()
{
}

void CUIBoardButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/panel-info.png", NULL, NULL, m_vPosition);
	//m_pText = new CUIText("UI_TEST");

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/panel-info.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}

