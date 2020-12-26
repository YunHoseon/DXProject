#include "stdafx.h"
#include "CUI2LevelCombinatorImage.h"
#include "CUITexture.h"


CUI2LevelCombinatorImage::CUI2LevelCombinatorImage(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUI2LevelCombinatorImage::~CUI2LevelCombinatorImage()
{
}

void CUI2LevelCombinatorImage::Setup()
{
	m_pTexture = new CUITexture("data/UI/2LevelMix.png", "data/UI/2LevelMix.png", "data/UI/2LevelMix.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/2LevelMix.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
