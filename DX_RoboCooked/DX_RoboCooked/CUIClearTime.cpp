#include "stdafx.h"
#include "CUIClearTime.h"
#include "CUITexture.h"


CUIClearTime::CUIClearTime(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_vPosition = vPos;
	Setup();
}


CUIClearTime::~CUIClearTime()
{
}

void CUIClearTime::Setup()
{
	m_pTexture = new CUITexture("data/UI/clearTime.png", NULL, NULL, m_vPosition);
}
