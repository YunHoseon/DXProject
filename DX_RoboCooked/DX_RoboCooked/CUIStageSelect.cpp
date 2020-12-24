#include "stdafx.h"
#include "CUIStageSelect.h"
#include "CUIStageSelectPopUpBoard.h"
#include "CUISelectSolved.h"
#include "CUISelectUnsolved.h"
#include "CUISelectMainButton.h"
#include "CUISelectLeft.h"
#include "CUISelectRight.h"
#include "CGameScene.h"
#include <fstream>


CUIStageSelect::CUIStageSelect(D3DXVECTOR2 vPos):m_nPage(0), m_nMaxPage(0)
{
	m_vPosition = vPos;
	Setup();

	g_EventManager->Attach(eEvent::StageClose, this);

	g_EventManager->Attach(eEvent::SelectButton1, this);
	g_EventManager->Attach(eEvent::SelectButton2, this);
	g_EventManager->Attach(eEvent::SelectButton3, this);
	g_EventManager->Attach(eEvent::SelectButton4, this);
	g_EventManager->Attach(eEvent::SelectButton5, this);
	g_EventManager->Attach(eEvent::SelectButton6, this);

	g_EventManager->Attach(eEvent::SelectLeft, this);
	g_EventManager->Attach(eEvent::SelectRight, this);


}

CUIStageSelect::~CUIStageSelect()
{
}

void CUIStageSelect::Setup()
{
	
	Load();
}

void CUIStageSelect::Load()
{

	std::ifstream is("data/js/SaveData.json");
	is >> m_jSaveData;
	is.close();
	CUIStageSelectPopUpBoard* board = new CUIStageSelectPopUpBoard(m_vPosition);
	{
		AddChild(board);
		
		CUI* Select = nullptr;
		for (int i = 0 , iBtnNumber = 0; i < m_jSaveData.size(); ++i , ++iBtnNumber)
		{
			if (iBtnNumber == 6)
			{
				iBtnNumber = 0;
				m_nMaxPage++;
			}
			string stageID = m_jSaveData[i]["StageID"];
			float fTime  = m_jSaveData[i]["ClearTime"];
			int isClear;
			if (i == 0)
			{
				isClear = true;
			}
			else
			{
				isClear = m_jSaveData[i-1]["isClear"];
			}
			


			D3DXVECTOR2 vPos = board->GetSelectPosition(iBtnNumber);
			eBtnEvent ebtn;

			switch (iBtnNumber)
			{
			case 0:
				ebtn = eBtnEvent::SelectButton1;
				break;
			case 1:
				ebtn = eBtnEvent::SelectButton2;
				break;
			case 2:
				ebtn = eBtnEvent::SelectButton3;
				break;
			case 3:
				ebtn = eBtnEvent::SelectButton4;
				break;
			case 4:
				ebtn = eBtnEvent::SelectButton5;
				break;
			case 5:
				ebtn = eBtnEvent::SelectButton6;
				break;
			}

			if (isClear)
			{
				Select = new CUISelectSolved(vPos, stageID, fTime, m_nMaxPage,ebtn);
			}
			else
			{
				Select = new CUISelectUnsolved(vPos, stageID, fTime, m_nMaxPage);
			}


			board->AddChild(Select);
			
		}

		CUI* left = new CUISelectLeft(board->GetLeftPosition(), eBtnEvent::SelectLeft);
		AddChild(left);

		CUI* right = new CUISelectRight(board->GetRightPosition(), eBtnEvent::SelectRight);
		AddChild(right);

		CUI* main = new CUISelectMainButton(board->GetMainPosition(), eBtnEvent::StageClose);
		AddChild(main);
	}
}

bool CUIStageSelect::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::MouseClick:
		MouseClickEvent(_value);
		break;
	case eEvent::MouseHover:
		MouseHoverEvent(_value);
		break;
	case eEvent::MouseRelease:
	{
		MouseReleaseEvent(_value);
		return m_isActive;
	}
		break;
	case eEvent::StageClose:
	{
		ActiveUI();
		g_EventManager->CallEvent(eEvent::MainEvent, NULL);
	}
		break;
	case eEvent::SelectButton1:
		SelectEvent(0);
		break;
	case eEvent::SelectButton2:
		SelectEvent(1);
		break;
	case eEvent::SelectButton3:
		SelectEvent(2);
		break;
	case eEvent::SelectButton4:
		SelectEvent(3);
		break;
	case eEvent::SelectButton5:
		SelectEvent(4);
		break;
	case eEvent::SelectButton6:
		SelectEvent(5);
		break;
	case eEvent::SelectLeft:
	{
		m_nPage--;
		if (m_nPage < 0)
			m_nPage = 0;
		ActivePage(m_nPage);
	}
		break;
	case eEvent::SelectRight:
	{
		m_nPage++;
		if (m_nPage > m_nMaxPage)
			m_nPage = m_nMaxPage;
		ActivePage(m_nPage);
	}
		break;
	}
	return true;
}

void CUIStageSelect::SelectEvent(int i)
{
	if (m_jSaveData[i + m_nPage]["FileName"] == "X")
		return;

	CGameScene* scene = new CGameScene;
	g_pThreadManager->AddThread(thread(&CGameScene::Load, scene, "data/js", m_jSaveData[i + m_nPage]["FileName"], &CGameScene::Init));

	CScene* pBeforeScene = g_SceneManager->SetCurrentScene(scene);
	if (pBeforeScene)
	{
		g_pThreadManager->AddThread(thread([pBeforeScene]() { delete pBeforeScene; }));
	}
}

void CUIStageSelect::ActiveUI()
{
	InvertActive();
	ActivePage(m_nPage);
	CheckActiveEvent();
}


