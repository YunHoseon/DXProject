#include "stdafx.h"
#include "CMonster.h"

CMonster::CMonster(IInteractCenter* pInteractCenter) 
			: m_pInteractCenter(pInteractCenter)
			, m_nSpinParts(0)
{
	g_EventManager->Attach(eEvent::PartsSpin, this);
}

CMonster::~CMonster()
{
	g_EventManager->Detach(eEvent::Player1KeyChange, this);
}

void CMonster::Update()
{
	if (Istriggered())
	{
		m_pInteractCenter->CC(ChooseCC());
	}
	
}

void CMonster::Render()
{
}


CCrowdControl * CMonster::ChooseCC()
{
	//return m_arrCC[0].Clone();
	return nullptr;
}

void CMonster::OnEvent(eEvent eEvent, void * _value)
{
	switch (eEvent)
	{
	case eEvent::PartsSpin:
		SpinPartsSkill();
		break;
	}
}

bool CMonster::Istriggered()
{
	if (m_nSpinParts % 4 == 0)
		return true;
	

	return false;
}

void CMonster::SpinPartsSkill()
{
	m_nSpinParts++;
}
