#include "stdafx.h"
#include "CUIloadingMessageComplete.h"
#include "CUITexture.h"

CUIloadingMessageComplete::CUIloadingMessageComplete(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	m_isActive = true;
	Setup();
}


CUIloadingMessageComplete::~CUIloadingMessageComplete()
{
}

void CUIloadingMessageComplete::Setup()
{
	m_pTexture = new CUITexture("data/UI/loadingMessage_complete.png", NULL, NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/loadingMessage_complete.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
