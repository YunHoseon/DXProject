#include "stdafx.h"
#include "CUIWhiteboard.h"
#include "CUISubWhiteboard.h"

CUIWhiteboard::CUIWhiteboard()
{
	m_isActive = false;
	m_vPosition = D3DXVECTOR2(0, 0);
	Setup();
}


CUIWhiteboard::~CUIWhiteboard()
{
}

void CUIWhiteboard::Setup()
{
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	CUI* board = new CUISubWhiteboard(D3DXVECTOR2(vp.Width / 2 - 584,vp.Height / 2 - 475));
	AddChild(board);
}