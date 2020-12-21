#include "stdafx.h"
#include "CCCStopMove.h"

#include "CUICC.h"


CCCStopMove::CCCStopMove() : CCrowdControl()
{
	m_pImage = new CUICC("data/UI/bubble_cc_cantMove.png", nullptr, nullptr);
}

CCCStopMove::CCCStopMove(CCCStopMove* clone):
	CCrowdControl(clone)
{
}

CCCStopMove::~CCCStopMove()
{
	SafeDelete(m_pImage);
}

void CCCStopMove::Render()
{
	if (m_pImage)
		m_pImage->Render();
}

void CCCStopMove::SetTarget(D3DXVECTOR3* target)
{
	if (m_pImage)
		m_pImage->SetTargetPosition(target);
}


