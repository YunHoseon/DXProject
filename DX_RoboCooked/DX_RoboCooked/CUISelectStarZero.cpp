#include "stdafx.h"
#include "CUISelectStarZero.h"
#include "CUITexture.h"

CUISelectStarZero::CUISelectStarZero(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUISelectStarZero::~CUISelectStarZero()
{
}

void CUISelectStarZero::Setup()
{
	m_pTexture = new CUITexture("data/UI/Stage/select_rank_0.png", "data/UI/Stage/select_rank_0.png", "data/UI/Stage/select_rank_0.png", m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_rank_0.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
