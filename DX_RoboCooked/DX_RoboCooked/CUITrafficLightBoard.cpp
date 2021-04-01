#include "stdafx.h"
#include "CUITrafficLightBoard.h"

CUITrafficLightBoard::CUITrafficLightBoard()
{
}

CUITrafficLightBoard::~CUITrafficLightBoard()
{
}

void CUITrafficLightBoard::SetPosition()
{
	D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);
	m_vPosition = D3DXVECTOR2((vp.Width - m_vSize.x) / 2, vp.Height - m_vSize.y);
}
