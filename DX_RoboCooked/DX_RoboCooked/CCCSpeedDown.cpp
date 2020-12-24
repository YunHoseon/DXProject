#include "stdafx.h"
#include "CCCSpeedDown.h"
#include "CUICC.h"

CCCSpeedDown::CCCSpeedDown() : CCrowdControl()
{
	m_pImage = new CUICC("data/ui/bubble_cc_slow.png", nullptr, nullptr);
}

CCCSpeedDown::CCCSpeedDown(CCCSpeedDown * clone) : CCrowdControl()
{
	m_pImage = new CUICC("data/ui/bubble_cc_slow.png", nullptr, nullptr);
}

CCCSpeedDown::~CCCSpeedDown()
{
	SafeDelete(m_pImage);
}

void CCCSpeedDown::Render()
{
	if (m_pImage)
		m_pImage->Render();
}

void CCCSpeedDown::SetTarget(D3DXVECTOR3 * target)
{
	if (m_pImage)
		m_pImage->SetTargetPosition(target);
}
