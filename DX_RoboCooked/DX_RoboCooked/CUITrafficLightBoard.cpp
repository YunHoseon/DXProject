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
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vPosition = D3DXVECTOR2((rc.right - m_vSize.x) / 2, rc.bottom - m_vSize.y);

}
