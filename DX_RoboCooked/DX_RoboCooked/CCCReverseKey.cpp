#include "stdafx.h"
#include "CCCReverseKey.h"

#include "CUICC.h"


CCCReverseKey::CCCReverseKey() : CCrowdControl()
{
	m_pImage = new CUICC("bubble_cc_reverseMove.png", nullptr, nullptr);
}

CCCReverseKey::CCCReverseKey(CCCReverseKey* clone) : CCrowdControl(clone)
{
	m_pImage = new CUICC("bubble_cc_reverseMove.png", nullptr, nullptr);
}

CCCReverseKey::~CCCReverseKey()
{
	SafeDelete(m_pImage);
}

void CCCReverseKey::Render()
{
	if (m_pImage)
		m_pImage->Render();
}

void CCCReverseKey::SetTarget(D3DXVECTOR3* target)
{
	if (m_pImage)
		m_pImage->SetTargetPosition(target);
}

