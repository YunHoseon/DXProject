#include "stdafx.h"
#include "CUI.h"


CUI::CUI()
	: m_pParent(nullptr)
	, m_vPosition(0,0)
	, m_vSize(0,0)
	, m_eUIState(eUIState::Disabled)
	, m_eUIPastState(eUIState::Disabled)
	, m_isActive(false)
	, m_isPress(false)
	, m_eBtnEvent(eBtnEvent::None)
{

}


CUI::~CUI()
{
	for (list<CUI*>::value_type p : m_listUIchildren)
	{
		SafeDelete(p);
	}
}

void CUI::SetParent(CUI * parent)
{
	this->m_pParent = parent;
}

void CUI::CheckPressIn(POINT pt)
{
	for (auto it : m_listUIchildren)
	{
		if (it->m_vPosition.x <= pt.x && it->m_vPosition.x + it->m_vSize.x >= pt.x
			&& it->m_vPosition.y <= pt.y && it->m_vPosition.y + it->m_vSize.y >= pt.y)
		{
			if (it->GetlistUIchildrenSize() == 0)
			{
				if (it->m_isPress == false)
				{
					it->m_isPress = true;
				}
			}
		}
	}
}

void CUI::CheckReleaseIn(POINT pt)
{
	for (auto it : m_listUIchildren)
	{
		if (it->m_vPosition.x <= pt.x && it->m_vPosition.x + it->m_vSize.x >= pt.x
			&& it->m_vPosition.y <= pt.y && it->m_vPosition.y + it->m_vSize.y >= pt.y)
		{

			if (it->GetlistUIchildrenSize() == 0)
			{
				if (it->m_isPress)
				{
					if (it->GetUIState() == eUIState::Hover)
					{
						//it->SetUIState(eUIState::Active);
						it->ButtonEvent(it->m_eBtnEvent);
					}
					else if (it->GetUIState() == eUIState::Active)
					{
						it->SetUIState(eUIState::Disabled);
					}
				}
			}
		}
		it->m_isPress = false;
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

void CUI::InvertActive()
{
	for (auto it : m_listUIchildren)
	{
		it->InvertActive();
	}
	m_isActive = !m_isActive;
}

void CUI::ButtonEvent(eBtnEvent btnEvent)
{
	switch (btnEvent)
	{
	case eBtnEvent::PauseMain:
		g_EventManager->CallEvent(eEvent::PauseMain, NULL);
		break;
	case eBtnEvent::PauseClose:
		g_EventManager->CallEvent(eEvent::PauseClose, NULL);
		break;
	case eBtnEvent::PauseReset:
		g_EventManager->CallEvent(eEvent::PauseReset, NULL);
		break;
	case eBtnEvent::PauseEnd:
		g_EventManager->CallEvent(eEvent::PauseEnd, NULL);
		break;
	}
}

void CUI::InitUIState()
{
	for (CUI* it : m_listUIchildren)
	{
		it->m_eUIState = eUIState::Disabled;
	}
}

void CUI::SetActiveUIState(int n)
{
	InitUIState();
	int cnt = 0;
	for (CUI* it : m_listUIchildren)
	{
		if (cnt == n)
			return;
	
		it->SetUIState(eUIState::Active);
		cnt++;
	}
}

void CUI::AddPosition(float x, float y)
{
	m_vPosition.x += x;
	m_vPosition.y += y;
	for (CUI* p : m_listUIchildren)
	{
		p->AddPosition(x, y);
	}
}
