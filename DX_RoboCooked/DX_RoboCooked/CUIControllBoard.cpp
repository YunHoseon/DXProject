#include "stdafx.h"
#include "CUIControllBoard.h"
#include "CUITexture.h"

//popUp_controll.png
CUIControllBoard::CUIControllBoard()
{
	Setup();
}


CUIControllBoard::~CUIControllBoard()
{
}

void CUIControllBoard::Setup()
{
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Main/popUp_controll.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vPosition = D3DXVECTOR2((rc.right - m_vSize.x) / 2, 50);

	m_pTexture = new CUITexture("data/UI/Main/popUp_controll.png", NULL, NULL, m_vPosition);
}
