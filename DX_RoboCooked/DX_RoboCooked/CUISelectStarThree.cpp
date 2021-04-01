#include "stdafx.h"
#include "CUISelectStarThree.h"
#include "CUITexture.h"


CUISelectStarThree::CUISelectStarThree(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUISelectStarThree::~CUISelectStarThree()
{
}

void CUISelectStarThree::Setup()
{
	m_pTexture = new CUITexture("data/UI/Stage/select_rank_3.png", "data/UI/Stage/select_rank_3.png", "data/UI/Stage/select_rank_3.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_rank_3.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
