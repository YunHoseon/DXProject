#include "stdafx.h"
#include "CUIAcidRain.h"

#include "CUITexture.h"

void CUIAcidRain::Setup()
{
}

CUIAcidRain::CUIAcidRain() :
	m_fDuration(0.5f),
	m_fElapsedTime(0)
{
	CUITexture* rain1 = new CUITexture("data/ui/acid_rain.png", nullptr, nullptr, D3DXVECTOR2(-480, 0));
	CUITexture* rain2 = new CUITexture("data/ui/acid_rain.png", nullptr, nullptr, D3DXVECTOR2(-480 + 1920, 0));
	AddChild(rain1);
	AddChild(rain2);
}

CUIAcidRain::~CUIAcidRain()
{
}

void CUIAcidRain::Update()
{
	if(m_isActive)
	{
		static int i = 1;
		m_fElapsedTime += g_pTimeManager->GetElapsedTime();
		if(m_fElapsedTime >= m_fDuration)
		{
			AddPosition(480 * i, 0);
			i *= -1;
			m_fElapsedTime = 0;
		}
	}
}

void CUIAcidRain::Render()
{
	if(m_isActive)
	{
		Update();
		for (list<CUI*>::value_type p : m_listUIchildren)
		{
			p->Render();
		}
	}
}

bool CUIAcidRain::OnEvent(eEvent eEvent, void* _value)
{
	return true;
}
