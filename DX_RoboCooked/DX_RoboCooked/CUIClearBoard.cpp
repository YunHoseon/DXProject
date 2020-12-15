#include "stdafx.h"
#include "CUIClearBoard.h"
#include "CUITexture.h"
#include "CUIText.h"


CUIClearBoard::CUIClearBoard(D3DXVECTOR2 vPos, string sText, eBtnEvent btnEvent)
{
	m_sTimeText = sText;

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

	D3DXVECTOR2 textPositon = m_vPosition;
	textPositon.x += 350;
	textPositon.y += 400;

	m_pText = new CUIText(m_sTimeText, textPositon);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/popUp_clear.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
