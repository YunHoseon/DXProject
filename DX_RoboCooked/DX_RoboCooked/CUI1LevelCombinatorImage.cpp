#include "stdafx.h"
#include "CUI1LevelCombinatorImage.h"
#include "CUITexture.h"


CUI1LevelCombinatorImage::CUI1LevelCombinatorImage(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUI1LevelCombinatorImage::~CUI1LevelCombinatorImage()
{
}

void CUI1LevelCombinatorImage::Setup()
{
	m_pTexture = new CUITexture("data/UI/1LevelMix.png", "data/UI/1LevelMix.png", "data/UI/1LevelMix.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/1LevelMix.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
