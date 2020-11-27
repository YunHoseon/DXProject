#include "stdafx.h"
#include "CUI.h"


CUI::CUI()
	: m_pParent(nullptr)
	, m_pParentWorldTM(nullptr)
	, m_vPosition(0,0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


CUI::~CUI()
{
}

void CUI::SetParent(CUI * parent)
{
	this->m_pParent = parent;
	m_pParentWorldTM = &parent->m_matWorld;
}



