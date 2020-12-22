#include "stdafx.h"
#include "CUI.h"
//юс╫ц
#include "CGameScene.h"

float CUI::m_fHeightRevision = 0;
float CUI::m_fWidthRevision = 0;

CUI::CUI() :
	m_pParent(nullptr),
	m_vPosition(0, 0),
	m_vTextPosition(0,0),
	m_vSize(0, 0),
	m_eUIState(eUIState::Up),
	m_eUIPastState(eUIState::Up),
	m_isActive(false),
	m_isPress(false),
	m_eBtnEvent(eBtnEvent::None),
	m_matWorld(g_matIdentity),
	m_pTargetPosition(nullptr),
	m_pTargetWorldTM(nullptr),
	m_isMouseDown(false)
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
	//for (auto it : m_listUIchildren)
	//{
	//	if (it->m_vPosition.x * m_fWidthRevision <= pt.x && (it->m_vPosition.x + it->m_vSize.x) * m_fWidthRevision >= pt.x
	//		&& it->m_vPosition.y * m_fHeightRevision <= pt.y && (it->m_vPosition.y + it->m_vSize.y) * m_fHeightRevision >= pt.y)
	//	{
	//		if (it->GetlistUIchildrenSize() == 0)
	//		{
	//			if (it->m_isPress == false)
	//			{
	//				it->m_isPress = true;
	//			}
	//		}
	//	}
	//}
	if (m_vPosition.x * m_fWidthRevision <= pt.x && (m_vPosition.x + m_vSize.x) * m_fWidthRevision >= pt.x
		&&m_vPosition.y * m_fHeightRevision <= pt.y && (m_vPosition.y + m_vSize.y) * m_fHeightRevision >= pt.y)
	{
		if (GetlistUIchildrenSize() == 0)
		{
			if (m_isPress == false)
			{
				m_isPress = true;
			}
		}
		else
		{
			for (auto it : m_listUIchildren)
			{
				it->CheckPressIn(pt);
			}
		}
	}

	
}

void CUI::CheckReleaseIn(POINT pt)
{
	//for (auto it : m_listUIchildren)
	//{
	//	if (it->m_vPosition.x * m_fWidthRevision <= pt.x && (it->m_vPosition.x + it->m_vSize.x) * m_fWidthRevision >= pt.x
	//		&& it->m_vPosition.y * m_fHeightRevision <= pt.y && (it->m_vPosition.y + it->m_vSize.y) * m_fHeightRevision >= pt.y)
	//	{
	//		if (it->GetlistUIchildrenSize() == 0)
	//		{
	//			if (it->m_isPress)
	//			{
	//				if (it->GetUIState() == eUIState::Hover)
	//				{
	//					//it->SetUIState(eUIState::Active);
	//					it->ButtonEvent(it->m_eBtnEvent);
	//				}
	//				else if (it->GetUIState() == eUIState::Down)
	//				{
	//					it->SetUIState(eUIState::Up);
	//				}
	//			}
	//		}
	//	}
	//	it->m_isPress = false;
	//}

	
	if (m_vPosition.x * m_fWidthRevision <= pt.x && (m_vPosition.x + m_vSize.x) * m_fWidthRevision >= pt.x
		&& m_vPosition.y * m_fHeightRevision <= pt.y && (m_vPosition.y + m_vSize.y) * m_fHeightRevision >= pt.y)
	{
		if (GetlistUIchildrenSize() == 0)
		{
			if (m_isPress)
			{
				if (GetUIState() == eUIState::Hover)
				{
					//SetUIState(eUIState::Active);
					ButtonEvent(m_eBtnEvent);
				}
				else if (GetUIState() == eUIState::Down)
				{
					SetUIState(eUIState::Up);
				}
			}
		}
		else
		{
			for (auto it : m_listUIchildren)
			{
				it->CheckReleaseIn(pt);
			}
		}
	}
	m_isPress = false;
}

void CUI::CheckInHover(POINT pt)
{
	if (m_isActive == false)
		return;

	//for (auto it : m_listUIchildren)
	//{
	//	if (it->m_vPosition.x * m_fWidthRevision <= pt.x && (it->m_vPosition.x + it->m_vSize.x) * m_fWidthRevision >= pt.x
	//		&& it->m_vPosition.y * m_fHeightRevision <= pt.y && (it->m_vPosition.y + it->m_vSize.y) * m_fHeightRevision >= pt.y)
	//	{
	//		if (it->GetlistUIchildrenSize() == 0)
	//		{
	//			if (it->GetUIState() == eUIState::Down)
	//				return;

	//			it->SetUIPastState(it->GetUIState());
	//			it->SetUIState(eUIState::Hover);
	//		}
	//		else
	//		{
	//			it->CheckInHover(pt);
	//		}
	//	}
	//	else if (it->GetUIState() == eUIState::Hover)
	//	{
	//		it->SetUIState(it->GetUIPastState());
	//	}	
	//}

	
	if (m_vPosition.x * m_fWidthRevision <= pt.x && (m_vPosition.x + m_vSize.x) * m_fWidthRevision >= pt.x
		&& m_vPosition.y * m_fHeightRevision <= pt.y && (m_vPosition.y + m_vSize.y) * m_fHeightRevision >= pt.y)
	{
		if (GetlistUIchildrenSize() == 0)
		{
			if (GetUIState() == eUIState::Down)
				return;

			SetUIPastState(GetUIState());
			SetUIState(eUIState::Hover);
		}
		else
		{
			for (auto it : m_listUIchildren)
			{
				it->CheckInHover(pt);
			}
		}
	}
	else if (GetUIState() == eUIState::Hover)
	{
		SetUIState(GetUIPastState());
	}
}

void CUI::InvertActive()
{
	for (auto it : m_listUIchildren)
	{
		it->InvertActive();
	}
	m_isActive = !m_isActive;
}

void CUI::ActiveUI()
{
	InvertActive();
	CheckActiveEvent();
}

void CUI::CheckActiveEvent()
{
	for (auto it : m_listUIchildren)
	{
		it->CheckActiveEvent();
	}

	if (m_isActive)
	{
		g_EventManager->Attach(eEvent::MouseRelease, this);
		g_EventManager->Attach(eEvent::MouseClick, this);
		g_EventManager->Attach(eEvent::MouseHover, this);
	}
	else
	{
		g_EventManager->Detach(eEvent::MouseClick, this);
		g_EventManager->Detach(eEvent::MouseHover, this);
	}
}

void CUI::SetActive(bool is)
{
	for (auto it : m_listUIchildren)
	{
		it->SetActive(is);
	}
	m_isActive = is;
}

void CUI::SetChildActive(bool is)
{
	for (auto it : m_listUIchildren)
	{
		it->m_isActive = is;
	}
}

void CUI::ButtonEvent(eBtnEvent btnEvent)
{
	g_SoundManager->PlaySFX("click");
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
	case eBtnEvent::ControllClose:
		g_EventManager->CallEvent(eEvent::ControllClose, NULL);
		break;
	case eBtnEvent::StageClose:
		g_EventManager->CallEvent(eEvent::StageClose, NULL);
		break;
	case eBtnEvent::STAGE1_1:
	{
			CGameScene* scene = new CGameScene;
			thread _t1(&CGameScene::Load, scene, "data/js", "AllTest.json", &CGameScene::Init);
			_t1.detach();
		
			CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
			if (pBeforeScene)
			{
				thread _t2([pBeforeScene]() { delete pBeforeScene; });
				_t2.detach();
			}
	}
		break;
	}
}

void CUI::InitUIState()
{
	for (CUI* it : m_listUIchildren)
	{
		it->m_eUIState = eUIState::Up;
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
	
		it->SetUIState(eUIState::Down);
		cnt++;
	}
}

void CUI::SetActiveUIState()
{
	InitUIState();
	for (CUI* it : m_listUIchildren)
	{
		it->SetUIState(eUIState::Down);
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
