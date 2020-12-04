#include "stdafx.h"
#include "CMonster.h"

CMonster::CMonster(IInteractCenter* pInteractCenter) 
			: m_pInteractCenter(pInteractCenter)
			, m_eSkillCondition()
			, m_eSkillEvent(eEvent::None)
			, m_fFirstSkillCoolDownTime(0.0f)
			, m_fFirstSkillElapsedTime(0.0f)
			, m_isArrive(false)
			, m_fTravelDistance(0.0f)
			, m_nCombinUseCount(0)
			, m_nVendingUseCount(0)
			, m_nCrowdControlCount(0)
			, m_nThrowPartsCount(0)
			, m_nSpinPartsCount(0)
			, m_SkillUsing(eSkill::None)
{
	ChooseSkillCondition();
}

CMonster::~CMonster()
{
	Destroy();
}

void CMonster::Update()
{
	if (FirstSkillTriggered())
	{
		FirstSkill();
	}


	if (SecondSkillTriggered())
	{
		SecondSkill();
		ChooseSkillCondition();
	}

	//m_pInteractCenter->CC(ChooseCC());
	
}

void CMonster::Render()
{
}

void CMonster::Destroy()
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
	case eEvent::SpinParts:
		SpinPartsSkill();
		break;
	case eEvent::ThrowParts:
		ThrowPartsSkill();
		break;
	case eEvent::CrowdControl:
		CrowdControlSkill();
		break;
	case eEvent::VendingUse:
		VendingUseSkill();
		break;
	case eEvent::CombinUse:
		CombinUseSkill();
		break;
	case eEvent::SpecificArea:
		ArriveSkill();
		break;
	case eEvent::TravelDistance:
		TravelDistanceSkill(_value);
		break;
	}

}

bool CMonster::SecondSkillTriggered()
{
	if (m_fTravelDistance >= 25.0f)
		return true;

	if (m_isArrive)
		return true;

	if (m_nCombinUseCount >= 4)
		return true;

	if (m_nVendingUseCount >= 4)
		return true;

	if (m_nCrowdControlCount >= 2)
		return true;

	if (m_nThrowPartsCount >= 4)
		return true;

	if (m_nSpinPartsCount >= 5)
		return true;

	return false;
}

bool CMonster::FirstSkillTriggered()
{
	m_fFirstSkillElapsedTime += g_pTimeManager->GetElapsedTime();

	if (m_fFirstSkillElapsedTime >= m_fFirstSkillCoolDownTime)
	{
		m_fFirstSkillElapsedTime = 0;
		return true;
	}

	return false;
}

void CMonster::ChooseSkillCondition()
{
	SkillConditionInit();

	int random = rand() % 100;

	{
		if (random < 16)
		{
			m_eSkillCondition = eSkillCondition::TravelDistance;
			g_EventManager->Attach(eEvent::TravelDistance, this);
			m_eSkillEvent = eEvent::TravelDistance;
		}
		else if (random < 30)
		{
			m_eSkillCondition = eSkillCondition::SpecificArea;
			g_EventManager->Attach(eEvent::SpecificArea, this);
			m_eSkillEvent = eEvent::SpecificArea;
		}
		else if (random < 48)
		{
			m_eSkillCondition = eSkillCondition::CombinUse;
			g_EventManager->Attach(eEvent::CombinUse, this);
			m_eSkillEvent = eEvent::CombinUse;
		}
		else if (random < 62)
		{
			m_eSkillCondition = eSkillCondition::VendingUse;
			g_EventManager->Attach(eEvent::VendingUse, this);
			m_eSkillEvent = eEvent::VendingUse;
		}
		else if (random < 74)
		{
			m_eSkillCondition = eSkillCondition::CrowdControl;
			g_EventManager->Attach(eEvent::CrowdControl, this);
			m_eSkillEvent = eEvent::CrowdControl;
		}
		else if (random < 86)
		{
			m_eSkillCondition = eSkillCondition::ThrowParts;
			g_EventManager->Attach(eEvent::ThrowParts, this);
			m_eSkillEvent = eEvent::ThrowParts;
		}
		else
		{
			m_eSkillCondition = eSkillCondition::SpinParts;
			g_EventManager->Attach(eEvent::SpinParts, this);
			m_eSkillEvent = eEvent::SpinParts;
		}
	}
	
}

void CMonster::TravelDistanceSkill(void * _value)
{
	ST_TravelDistanceEvent* data = static_cast<ST_TravelDistanceEvent*>(_value);

	m_fTravelDistance += data->fDistance;
}

void CMonster::SkillConditionInit()
{
	if (m_eSkillEvent == eEvent::None)
		return;
	g_EventManager->Detach(m_eSkillEvent, this);

	switch (m_eSkillEvent)
	{
	case eEvent::SpinParts:
		m_nSpinPartsCount = 0;
		break;
	case eEvent::ThrowParts:
		m_nThrowPartsCount = 0;
		break;
	case eEvent::CrowdControl:
		m_nCrowdControlCount = 0;
		break;
	case eEvent::VendingUse:
		m_nVendingUseCount = 0;
		break;
	case eEvent::CombinUse:
		m_nCombinUseCount = 0;
		break;
	case eEvent::SpecificArea:
		m_isArrive = false;
		break;
	case eEvent::TravelDistance:
		m_fTravelDistance = 0.0f;
		break;
	}
}