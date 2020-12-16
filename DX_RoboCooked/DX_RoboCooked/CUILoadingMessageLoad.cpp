#include "stdafx.h"
#include "CUILoadingMessageLoad.h"
#include "CUITexture.h"

CUILoadingMessageLoad::CUILoadingMessageLoad(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	m_isActive = true;
	Setup();
}


CUILoadingMessageLoad::~CUILoadingMessageLoad()
{
}

void CUILoadingMessageLoad::Setup()
{
	m_pTexture = new CUITexture("data/UI/loadingMessage_load.png", NULL, NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/loadingMessage_load.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
