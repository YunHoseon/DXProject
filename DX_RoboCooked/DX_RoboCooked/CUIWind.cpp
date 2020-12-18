#include "stdafx.h"
#include "CUIWind.h"

#include "CUITexture.h"

CUIWind::CUIWind():
	m_fDirect(1),
	m_fSpeed(10),
	m_fMargin(2158 - 1920)
{
	m_vPosition.x = 0;
	m_vPosition.y = 0;
	
	CUITexture* wind_l = new CUITexture("data/ui/SandWind_Left.png", nullptr, nullptr, D3DXVECTOR2(0, 0));
	CUITexture* wind_r = new CUITexture("data/ui/SandWind_Right.png", nullptr, nullptr, D3DXVECTOR2(-m_fMargin, 0));
	AddChild(wind_l);
	AddChild(wind_r);
}

CUIWind::~CUIWind()
{
}

void CUIWind::ResetPosition()
{
	m_listUIchildren.front()->SetPosition(0, 0);
	m_listUIchildren.back()->SetPosition(1920 - 2158, 0);
}

void CUIWind::SetAnimation(float fDirect)
{
	m_fDirect = fDirect;
	ResetPosition();
}

void CUIWind::Update()
{
	AddPosition(g_pTimeManager->GetElapsedTime() * m_fSpeed * m_fDirect, 0);
	if (m_vPosition.x < -m_fMargin || m_vPosition.x > m_fMargin)
		ResetPosition();
}

void CUIWind::Render()
{
	for (list<CUI*>::value_type p : m_listUIchildren)
	{
		p->Render();
	}
}
