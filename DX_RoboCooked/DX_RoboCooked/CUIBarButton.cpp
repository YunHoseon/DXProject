#include "stdafx.h"
#include "CUIBarButton.h"
#include "CUI.h"
#include "CUIText.h"
#include "CUITexture.h"

CUIBarButton::CUIBarButton(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIBarButton::~CUIBarButton()
{
}

void CUIBarButton::Setup()
{
	m_pTexture = new CUITexture("data/UI/btn-med-over.png", "data/UI/btn-med-down.png", NULL, m_vPosition);
	
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/btn-med-over.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
