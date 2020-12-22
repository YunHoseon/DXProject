#include "stdafx.h"
#include "CUISelectSolved.h"
#include "CUIText.h"
#include "CUISelectBoard.h"
#include "CUIStar.h"
#include "CUISelectStarZero.h"
#include "CUISelectStarOne.h"
#include "CUISelectStarTwo.h"
#include "CUISelectStarThree.h"
#include "CUIClearTime.h"
#include "CUISelectStartButton.h"




CUISelectSolved::CUISelectSolved(D3DXVECTOR2 vPos ,ST_GameData data, eBtnEvent eEvent) :CUISelect(vPos,data)
{
	m_eBtnEvent = eEvent;
	Setup();
}


CUISelectSolved::~CUISelectSolved()
{
}

void CUISelectSolved::Setup()
{
	CUI* board = new CUISelectBoard(m_vPosition, m_stData.chStageID);
	AddChild(board);

	CUI* star = nullptr;
	D3DXVECTOR2 starPos = D3DXVECTOR2(m_vPosition.x + 75, m_vPosition.y +65);
	switch (m_stData.nStarCount)
	{
	case 0:
		star = new CUISelectStarZero(starPos);
		break;
	case 1:
		star = new CUISelectStarOne(starPos);
		break;
	case 2:
		star = new CUISelectStarTwo(starPos);
		break;
	case 3:
		star = new CUISelectStarThree(starPos);
		break;
	}
	board->AddChild(star);
	D3DXVECTOR2 clearUIPos = D3DXVECTOR2(m_vPosition.x , m_vPosition.y + 150);
	D3DXVECTOR2 TimeTextPos = D3DXVECTOR2(m_vPosition.x + 285, m_vPosition.y + 190);

	CUI* clearTimeUI = new CUIClearTime(clearUIPos, TimeTextPos, m_stData.chGameTime, eTextType::SelectText);
	board->AddChild(clearTimeUI);

	D3DXVECTOR2 startBtnPos = D3DXVECTOR2(m_vPosition.x + 160, m_vPosition.y + 250);
	CUI* startbtn = new CUISelectStartButton(startBtnPos, m_eBtnEvent);
	board->AddChild(startbtn);
	



}

bool CUISelectSolved::OnEvent(eEvent eEvent, void * _value)
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
	}
	return true;
}
