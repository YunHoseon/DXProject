#include "stdafx.h"
#include "CUISelectNone.h"
#include "CUISelectBoard.h"
#include "CUIUpdateText.h"


CUISelectNone::CUISelectNone(D3DXVECTOR2 vPos, string chStageID, float fTime) :CUISelect(vPos,chStageID,fTime)
{
	Setup();
}


CUISelectNone::~CUISelectNone()
{
}

void CUISelectNone::Setup()
{
	CUI* board = new CUISelectBoard(m_vPosition, m_sStageID);
	AddChild(board);

	D3DXVECTOR2 textPos = D3DXVECTOR2(m_vPosition.x + 120, m_vPosition.y + 150);
	CUI* text = new CUIUpdateText(textPos);
	board->AddChild(text);

}
