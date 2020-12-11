#include "stdafx.h"
#include "CUITrafficLight.h"

CUITrafficLight::CUITrafficLight()
{
}

CUITrafficLight::~CUITrafficLight()
{
}

void CUITrafficLight::SetPosition()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vPosition = D3DXVECTOR2((rc.right - m_vSize.x) / 2, rc.bottom - m_vSize.y);

}
