#include "stdafx.h"
#include "CUI.h"


CUI::CUI()
	: m_pParent(nullptr)
	, m_pParentWorldTM(nullptr)
	, m_vPosition(0,0)
	, m_vSize(0,0)
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

bool CUI::CheckIn(POINT pt)
{
	if (m_vPosition.x <= pt.x && m_vPosition.x + m_vSize.x >= pt.x
		&& m_vPosition.y <= pt.y && m_vPosition.y + m_vSize.y >= pt.y)
		return true;
	return false;
}



