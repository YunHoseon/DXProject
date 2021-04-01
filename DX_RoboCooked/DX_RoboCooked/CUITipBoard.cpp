#include "stdafx.h"
#include "CUITipBoard.h"
#include "CUIPopUpBoard.h"
#include "CUITexture.h"
#include "CUITipBoardText.h"

CUITipBoard::CUITipBoard(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUITipBoard::~CUITipBoard()
{
}

void CUITipBoard::Setup()
{
	CUITexture* p = new CUITexture("data/ui/popUp_board_Tip.png", nullptr, nullptr, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/ui/popUp_board_Tip.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
	AddChild(p);
}

void CUITipBoard::SetText(string sText, int nWidth, int nHeight)
{
	 CUI* text = new CUITipBoardText(D3DXVECTOR2(m_vPosition.x + 135, m_vPosition.y + 175), sText,nWidth,nHeight);
	 AddChild(text);
}

void CUITipBoard::SetText(std::wstring wsText, int nWidth, int nHeight)
{
	CUI* text = new CUITipBoardText(D3DXVECTOR2(m_vPosition.x + 135, m_vPosition.y + 175), wsText, nWidth, nHeight);
	AddChild(text);

}
