#include "stdafx.h"
#include "CUIStarThree.h"
#include "CUITexture.h"


CUIStarThree::CUIStarThree(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIStarThree::~CUIStarThree()
{
}

void CUIStarThree::Setup()
{
	m_pTexture = new CUITexture("data/UI/rank_3.png", NULL, NULL, m_vPosition);
}
