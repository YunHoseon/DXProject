#include "stdafx.h"
#include "CUIClearBoard.h"
#include "CUITexture.h"
#include "CUIText.h"


CUIClearBoard::CUIClearBoard(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}


CUIClearBoard::~CUIClearBoard()
{
}

void CUIClearBoard::Setup()
{
	m_pTexture = new CUITexture("data/UI/popUp_clear.png", NULL, NULL, m_vPosition);
	m_pText = new CUIText("asd", m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/popUp_clear.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
