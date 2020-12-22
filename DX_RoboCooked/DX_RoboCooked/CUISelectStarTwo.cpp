#include "stdafx.h"
#include "CUISelectStarTwo.h"
#include "CUITexture.h"

CUISelectStarTwo::CUISelectStarTwo(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}

CUISelectStarTwo::~CUISelectStarTwo()
{
}

void CUISelectStarTwo::Setup()
{
	m_pTexture = new CUITexture("data/UI/Stage/select_rank_2.png", "data/UI/Stage/select_rank_2.png", "data/UI/Stage/select_rank_2.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_rank_2.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
