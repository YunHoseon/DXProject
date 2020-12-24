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




CUISelectSolved::CUISelectSolved(D3DXVECTOR2 vPos, string chStageID, float fTime, int nPage, eBtnEvent eEvent) :CUISelect(vPos, chStageID, fTime)
{
	m_eBtnEvent = eEvent;
	m_nUIPage = nPage;
	Setup();
}


CUISelectSolved::~CUISelectSolved()
{
}

void CUISelectSolved::Setup()
{
	CUI* board = new CUISelectBoard(m_vPosition, m_sStageID);
	AddChild(board);

	CUI* star = nullptr;
	D3DXVECTOR2 starPos = D3DXVECTOR2(m_vPosition.x + 75, m_vPosition.y +65);

	if (m_fGameTime >= 180)		star = new CUISelectStarThree(starPos);
	else if (m_fGameTime >= 120)star = new CUISelectStarTwo(starPos);
	else if (m_fGameTime >= 60)	star = new CUISelectStarOne(starPos);
	else						star = new CUISelectStarZero(starPos);

	string sTime = CalMin(m_fGameTime) + ":" + CalSec(m_fGameTime);
	board->AddChild(star);
	D3DXVECTOR2 clearUIPos = D3DXVECTOR2(m_vPosition.x , m_vPosition.y + 150);
	D3DXVECTOR2 TimeTextPos = D3DXVECTOR2(m_vPosition.x + 285, m_vPosition.y + 190);

	CUI* clearTimeUI = new CUIClearTime(clearUIPos, TimeTextPos, sTime, eTextType::SelectText);
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
