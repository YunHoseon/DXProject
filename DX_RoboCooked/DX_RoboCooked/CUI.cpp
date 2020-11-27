#include "stdafx.h"
#include "CUI.h"


CUI::CUI()
	: m_pParent(nullptr)
	, m_pParentWorldTM(nullptr)
{
	D3DXMatrixIdentity(&m_matWorld);
}


CUI::~CUI()
{
}



