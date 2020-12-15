#include "stdafx.h"
#include "CUIStarOne.h"
#include "CUITexture.h"


CUIStarOne::CUIStarOne(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIStarOne::~CUIStarOne()
{
}

void CUIStarOne::Setup()
{
	m_pTexture = new CUITexture("data/UI/rank_1.png", NULL, NULL, m_vPosition);
}
