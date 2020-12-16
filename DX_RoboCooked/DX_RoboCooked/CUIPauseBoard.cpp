#include "stdafx.h"
#include "CUIPauseBoard.h"
#include "CUI.h"
#include "CUITexture.h"


CUIPauseBoard::CUIPauseBoard(D3DXVECTOR2 vPos, eBtnEvent btnEvent)
{
	m_eBtnEvent = btnEvent;
	m_vPosition = vPos;
	Setup();
}


CUIPauseBoard::~CUIPauseBoard()
{
}

void CUIPauseBoard::Setup()
{

	m_pTexture = new CUITexture("data/UI/popUp_Pause.png", NULL, NULL, m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/popUp_Pause.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

	//RECT rc;
	//GetClientRect(g_hWnd, &rc);
	//m_vPosition = D3DXVECTOR2((rc.right - m_vSize.x) / 2, 50);



}

