#include "stdafx.h"
#include "CCCSlowAndStop.h"
#include "CUICC.h"

CCCSlowAndStop::CCCSlowAndStop() : CCrowdControl()
{
	m_pImage = new CUICC("data/ui/bubble_cc_slow.png", nullptr, nullptr);
}

CCCSlowAndStop::CCCSlowAndStop(CCCSlowAndStop * clone) : CCrowdControl()
{
	m_pImage = new CUICC("data/ui/bubble_cc_slow.png", nullptr, nullptr);
}

CCCSlowAndStop::~CCCSlowAndStop()
{
	SafeDelete(m_pImage);
}

void CCCSlowAndStop::Render()
{
	if (m_pImage)
		m_pImage->Render();
}

void CCCSlowAndStop::SetTarget(D3DXVECTOR3 * target)
{
	if (m_pImage)
		m_pImage->SetTargetPosition(target);
}
