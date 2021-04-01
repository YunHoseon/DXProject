#include "stdafx.h"
#include "CUISelectBoard.h"
#include "CUIText.h"
#include "CUITexture.h"


CUISelectBoard::CUISelectBoard(D3DXVECTOR2 vPos, string sText)
{
	m_vPosition = vPos;
	m_vTextPosition = D3DXVECTOR2(m_vPosition.x + 180, m_vPosition.y + 21);
	m_sText = sText;
	Setup();
}


CUISelectBoard::~CUISelectBoard()
{
}

void CUISelectBoard::Setup()
{
	m_pText = new CUIText(m_sText,m_vTextPosition, 40, 50, eTextType::SelectText);

	m_pTexture = new CUITexture("data/UI/Stage/select_board.png", "data/UI/Stage/select_board.png", "data/UI/Stage/select_board.png", m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_board.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
