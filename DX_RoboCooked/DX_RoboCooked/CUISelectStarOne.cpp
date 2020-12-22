#include "stdafx.h"
#include "CUISelectStarOne.h"
#include "CUITexture.h"


CUISelectStarOne::CUISelectStarOne(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUISelectStarOne::~CUISelectStarOne()
{
}

void CUISelectStarOne::Setup()
{
	m_pTexture = new CUITexture("data/UI/Stage/select_rank_1.png", "data/UI/Stage/select_rank_1.png", "data/UI/Stage/select_rank_1.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_rank_1.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
