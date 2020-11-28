#include "stdafx.h"
#include "CUI.h"


CUI::CUI()
	: m_pParent(nullptr)
	, m_vPosition(0,0)
	, m_vSize(0,0)
	, m_eUIState(eUIState::Disabled)
	, m_eUIPastState(eUIState::Disabled)
{

}


CUI::~CUI()
{
}

void CUI::SetParent(CUI * parent)
{
	this->m_pParent = parent;
}

//bool CUI::CheckIn(POINT pt)
//{
//	if (m_vPosition.x <= pt.x && m_vPosition.x + m_vSize.x >= pt.x
//		&& m_vPosition.y <= pt.y && m_vPosition.y + m_vSize.y >= pt.y)
//		return true;
//	return false;
//}



void CUI::CheckIn(POINT pt)
{
	for (auto it : m_listUIchildren)
	{
		if (it->m_vPosition.x <= pt.x && it->m_vPosition.x + it->m_vSize.x >= pt.x
			&& it->m_vPosition.y <= pt.y && it->m_vPosition.y + it->m_vSize.y >= pt.y)
		{
			if (it->GetlistUIchildrenSize() == 0)
			{
				if (it->GetUIState() == eUIState::Hover)
				{
					it->SetUIState(eUIState::Active);
				}
				else if (it->GetUIState() == eUIState::Active)
				{
					it->SetUIState(eUIState::Disabled);
				}
			}
			else
			{
				it->CheckIn(pt);
			}
		}
	}
}

void CUI::CheckInHover(POINT pt)
{
	for (auto it : m_listUIchildren)
	{
		if (it->m_vPosition.x <= pt.x && it->m_vPosition.x + it->m_vSize.x >= pt.x
			&& it->m_vPosition.y <= pt.y && it->m_vPosition.y + it->m_vSize.y >= pt.y)
		{
			if (it->GetlistUIchildrenSize() == 0)
			{
				if (it->GetUIState() == eUIState::Active)
					return;

				it->SetUIPastState(it->GetUIState());
				it->SetUIState(eUIState::Hover);
			}
			else
			{
				it->CheckInHover(pt);
			}
		}
		else if (it->GetUIState() == eUIState::Hover)
		{
			it->SetUIState(it->GetUIPastState());
		}	
	}
	return;
}
