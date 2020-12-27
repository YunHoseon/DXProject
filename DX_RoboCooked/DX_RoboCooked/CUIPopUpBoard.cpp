#include "stdafx.h"
#include "CUIPopUpBoard.h"
#include "CUITexture.h"


CUIPopUpBoard::CUIPopUpBoard(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIPopUpBoard::~CUIPopUpBoard()
{
}

void CUIPopUpBoard::Setup()
{
	m_pTexture = new CUITexture("data/UI/popUp_Board.png", NULL, NULL, m_vPosition);

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/popUp_Board.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
