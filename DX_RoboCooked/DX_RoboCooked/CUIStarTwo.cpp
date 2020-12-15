#include "stdafx.h"
#include "CUIStarTwo.h"
#include "CUITexture.h"

CUIStarTwo::CUIStarTwo(D3DXVECTOR2 vPos) 
{
	m_vPosition = vPos;
	Setup();
}

CUIStarTwo::~CUIStarTwo()
{
}

void CUIStarTwo::Setup()
{
	m_pTexture = new CUITexture("data/UI/rank_2.png", NULL, NULL, m_vPosition);
}
