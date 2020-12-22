#include "stdafx.h"
#include "CUIStageSelectPopUpBoard.h"
#include "CUITexture.h"

CUIStageSelectPopUpBoard::CUIStageSelectPopUpBoard(D3DXVECTOR2 vPos):m_vMainPosition(0,0)
{
	m_vPosition = vPos;
	Setup();
}


CUIStageSelectPopUpBoard::~CUIStageSelectPopUpBoard()
{
}

void CUIStageSelectPopUpBoard::Setup()
{

	m_vMainPosition = D3DXVECTOR2(m_vPosition.x + 770, m_vPosition.y + 980);

	m_vecSelectPosition.resize(6);
	m_vecSelectPosition[0] = D3DXVECTOR2(m_vPosition.x + 220, m_vPosition.y + 170);
	m_vecSelectPosition[1] = D3DXVECTOR2(m_vPosition.x + 600, m_vPosition.y + 170);
	m_vecSelectPosition[2] = D3DXVECTOR2(m_vPosition.x + 980, m_vPosition.y + 170);

	m_vecSelectPosition[3] = D3DXVECTOR2(m_vPosition.x + 220, m_vPosition.y + 550);
	m_vecSelectPosition[4] = D3DXVECTOR2(m_vPosition.x + 600, m_vPosition.y + 550);
	m_vecSelectPosition[5] = D3DXVECTOR2(m_vPosition.x + 980, m_vPosition.y + 550);

	m_pTexture = new CUITexture("data/UI/Stage/select_popUp.png", NULL, NULL, m_vPosition);
	D3DXIMAGE_INFO Info = g_pUITextureManager->GetTextureInfo("data/UI/Stage/select_popUp.png");
	m_vSize = D3DXVECTOR2(Info.Width, Info.Height);
}
