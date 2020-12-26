#include "stdafx.h"
#include "CUI1LevelCombination.h"
#include "CUITexture.h"


CUI1LevelCombination::CUI1LevelCombination(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUI1LevelCombination::~CUI1LevelCombination()
{
}

void CUI1LevelCombination::Setup()
{
	m_pTexture = new CUITexture("data/UI/1Level_Mix_Rc.png", "data/UI/1Level_Mix_Rc.png", "data/UI/1Level_Mix_Rc.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/1Level_Mix_Rc.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
