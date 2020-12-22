#include "stdafx.h"
#include "CUIUpdateText.h"
#include "CUIText.h"


CUIUpdateText::CUIUpdateText(D3DXVECTOR2 vPos)
{
	m_vTextPosition = vPos;
	Setup();
}


CUIUpdateText::~CUIUpdateText()
{
}

void CUIUpdateText::Setup()
{
	m_pText = new CUIText("Update...", m_vTextPosition, eTextType::UpdateText);
}
