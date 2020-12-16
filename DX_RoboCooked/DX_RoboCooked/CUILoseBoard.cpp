#include "stdafx.h"
#include "CUILoseBoard.h"
#include "CUITexture.h"


CUILoseBoard::CUILoseBoard()
{
	Setup();
}


CUILoseBoard::~CUILoseBoard()
{
}

void CUILoseBoard::Setup()
{

	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/popUp_lose.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vPosition = D3DXVECTOR2((rc.right - m_vSize.x) / 2, 50);
	m_pTexture = new CUITexture("data/UI/popUp_lose.png", NULL, NULL, m_vPosition);

}
