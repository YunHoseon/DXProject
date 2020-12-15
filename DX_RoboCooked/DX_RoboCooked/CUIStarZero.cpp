#include "stdafx.h"
#include "CUIStarZero.h"
#include "CUITexture.h"

CUIStarZero::CUIStarZero(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIStarZero::~CUIStarZero()
{
}

void CUIStarZero::Setup()
{
	m_pTexture = new CUITexture("data/UI/rank_0.png", NULL, NULL, m_vPosition);
}
