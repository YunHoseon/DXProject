#include "stdafx.h"
#include "CUIStageSelect.h"
#include "CUIStageSelectPopUpBoard.h"
#include "CUISelectSolved.h"
#include "CUISelectUnsolved.h"
#include "CUISelectNone.h"
#include "CUISelectMainButton.h"



CUIStageSelect::CUIStageSelect(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();

	g_EventManager->Attach(eEvent::StageClose, this);
}

CUIStageSelect::~CUIStageSelect()
{
}

void CUIStageSelect::Setup()
{
	CUIStageSelectPopUpBoard* board = new CUIStageSelectPopUpBoard(m_vPosition);
	AddChild(board);




	ST_GameData data;
	data.chGameTime = "02:30";
	data.chStageID = "1-1";
	data.nStarCount = 2;

	CUI* Select = new CUISelectSolved(board->GetSelectPosition(0), data,eBtnEvent::STAGE1_1);
	board->AddChild(Select);

	Select = new CUISelectUnsolved(board->GetSelectPosition(1), data);
	board->AddChild(Select);

	Select = new CUISelectUnsolved(board->GetSelectPosition(2), data);
	board->AddChild(Select);

	Select = new CUISelectNone(board->GetSelectPosition(3), data);
	board->AddChild(Select);

	Select = new CUISelectNone(board->GetSelectPosition(4), data);
	board->AddChild(Select);

	Select = new CUISelectNone(board->GetSelectPosition(5), data);
	board->AddChild(Select);

	CUI* main = new CUISelectMainButton(board->GetMainPosition() , eBtnEvent::StageClose);
	board->AddChild(main);
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
	}
	return true;
}
