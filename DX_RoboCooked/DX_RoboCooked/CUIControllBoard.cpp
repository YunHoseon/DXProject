#include "stdafx.h"
#include "CUIControllBoard.h"
#include "CUITexture.h"

//popUp_controll.png
CUIControllBoard::CUIControllBoard(D3DXVECTOR2 vPos)
{
	m_vPosition = vPos;
	Setup();
}


CUIControllBoard::~CUIControllBoard()
{
}

void CUIControllBoard::Setup()
{
	m_pTexture = new CUITexture("data/UI/Main/popUp_controll.png", NULL, NULL, m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Main/popUp_controll.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
