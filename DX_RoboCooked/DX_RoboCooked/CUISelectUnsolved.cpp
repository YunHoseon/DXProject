#include "stdafx.h"
#include "CUISelectUnsolved.h"
#include "CUIText.h"
#include "CUISelectBoard.h"
#include "CUIStar.h"
#include "CUISelectStarZero.h"
#include "CUISelectStarOne.h"
#include "CUISelectStarTwo.h"
#include "CUISelectStarThree.h"
#include "CUIClearTime.h"
#include "CUISelectStartButton.h"


CUISelectUnsolved::CUISelectUnsolved(D3DXVECTOR2 vPos, string chStageID, float fTime, int nPage):CUISelect(vPos,chStageID,fTime)
{

	m_nUIPage = nPage;
	Setup();
}


CUISelectUnsolved::~CUISelectUnsolved()
{
}

void CUISelectUnsolved::Setup()
{
	CUI* board = new CUISelectBoard(m_vPosition, m_sStageID);
	AddChild(board);

	D3DXVECTOR2 starPos = D3DXVECTOR2(m_vPosition.x + 75, m_vPosition.y + 65);
	CUI* star = new CUISelectStarZero(starPos);

	board->AddChild(star);
	D3DXVECTOR2 clearUIPos = D3DXVECTOR2(m_vPosition.x, m_vPosition.y + 150);
	D3DXVECTOR2 TimeTextPos = D3DXVECTOR2(m_vPosition.x + 285, m_vPosition.y + 190);

	CUI* clearTimeUI = new CUIClearTime(clearUIPos, TimeTextPos, "00:00", eTextType::SelectText);
	board->AddChild(clearTimeUI);

	//D3DXVECTOR2 startBtnPos = D3DXVECTOR2(m_vPosition.x + 160, m_vPosition.y + 250);
	//CUI* startbtn = new CUISelectStartButton(startBtnPos, m_eBtnEvent);
	//board->AddChild(startbtn);


}

bool CUISelectUnsolved::OnEvent(eEvent eEvent, void * _value)
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
