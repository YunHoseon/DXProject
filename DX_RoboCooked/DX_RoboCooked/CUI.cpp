#include "stdafx.h"
#include "CUI.h"


CUI::CUI()
	: m_pParent(nullptr)
	, m_vPosition(0,0)
	, m_vSize(0,0)
	, m_eUIState(eUIState::up)
	, m_eUIPastState(eUIState::up)
	, m_isActive(false)
	, m_isPress(false)
	, m_eBtnEvent(eBtnEvent::None)
{

}


CUI::~CUI()
{

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
					else if (it->GetUIState() == eUIState::down)
					{
						it->SetUIState(eUIState::up);
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
				if (it->GetUIState() == eUIState::down)
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
	case eBtnEvent::ClearMain:
		g_EventManager->CallEvent(eEvent::ClearMain, NULL);
		break;
	case eBtnEvent::ClearNextStage:
		g_EventManager->CallEvent(eEvent::ClearNextStage, NULL);
		break;
	case eBtnEvent::LoseMain:
		g_EventManager->CallEvent(eEvent::LoseMain, NULL);
		break;
	case eBtnEvent::LoseReset:
		g_EventManager->CallEvent(eEvent::LoseReset, NULL);
		break;
	case eBtnEvent::MainStart:
		g_EventManager->CallEvent(eEvent::MainStart, NULL);
		break;
	case eBtnEvent::MainControll:
		g_EventManager->CallEvent(eEvent::MainControll, NULL);
		break;
	case eBtnEvent::MainMaker:
		g_EventManager->CallEvent(eEvent::MainMaker, NULL);
		break;
	case eBtnEvent::MainEnd:
		g_EventManager->CallEvent(eEvent::MainEnd, NULL);
		break;
	case eBtnEvent::MakerClose:
		g_EventManager->CallEvent(eEvent::MakerClose, NULL);
		break;
	}

}

void CUI::InitUIState()
{
	for (CUI* it : m_listUIchildren)
	{
		it->m_eUIState = eUIState::up;
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
	
		it->SetUIState(eUIState::down);
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
