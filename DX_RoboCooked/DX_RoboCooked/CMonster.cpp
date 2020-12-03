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
	Destroy();
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

void CMonster::Destroy()
{
	g_EventManager->Detach(eEvent::PartsSpin, this);
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
	if (m_nSpinParts == 0)
		return false;
	
	if (m_nSpinParts % 4 == 0)
		return true;
	
	return false;
}

void CMonster::SpinPartsSkill()
{
	m_nSpinParts++;
}
