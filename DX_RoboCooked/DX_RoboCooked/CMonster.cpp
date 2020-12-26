#include "stdafx.h"
#include "CMonster.h"

CMonster::CMonster(IInteractCenter *pInteractCenter)
	: m_pInteractCenter(pInteractCenter), m_eSkillCondition(), m_eSecondSkillEvent(eEvent::None), m_fFirstSkillConditionTime(0.0f), m_fFirstSkillConditionElapsedTime(0.0f), m_isArrive(false), m_fTravelDistance(0.0f), m_nCombinUseCount(0), m_nVendingUseCount(0), m_nCrowdControlCount(0), m_nThrowPartsCount(0), m_nSpinPartsCount(0), m_sSpecificPartsID(""), m_fFirstSkillElapsedTime(0.0f), m_fSecondSkillElapsedTime(0.0f), m_fUltimateSkillElapsedTime(0.0f), m_fUltimateSkillConditionTime(999.0f), m_nBluePrintChangeCount(0), m_vSpecificAreaPosition(0, 0, 0)

{
	g_EventManager->Attach(eEvent::CompleteBluePrint, this);
}

CMonster::~CMonster()
{
	Destroy();
}

void CMonster::Update()
{
	if (FirstSkillTriggered() && m_pInteractCenter->CheckWarning())
	{
		m_stSkillUsing.FirstSkillProperty = FirstSkill();
		m_stSkillUsing.isFirstSkill = true;
		m_pInteractCenter->MonsterSkill(FirstSkill(), FirstSkillTime());
	}

	if (SecondSkillTriggered() && m_pInteractCenter->CheckWarning())
	{
		m_stSkillUsing.SecondSkillProperty = SecondSkill();
		m_stSkillUsing.isSecondSkill = true;
		ChooseSkillCondition();
		m_pInteractCenter->MonsterSkill(SecondSkill(), SecondSkillTime());
	}

	if (m_eSecondSkillEvent == eEvent::SpecificArea)
	{
		if (m_pInteractCenter->CheckDistanceToSelectedObject(m_vSpecificAreaPosition))
		{
			m_isArrive = true;
		}
	}

	if (UltimateSkillTriggered() && m_pInteractCenter->CheckWarning())
	{
		m_stSkillUsing.UltimateSkillProperty = UltimateSkill();
		m_stSkillUsing.isUltimateSkill = true;
		m_pInteractCenter->MonsterSkill(UltimateSkill(), UltimateSkillTime());
	}

	if (CheckDurationTimeFirstSkill())
	{
		m_pInteractCenter->FinishSkill(m_stSkillUsing.FirstSkillProperty);
		m_stSkillUsing.FirstSkillProperty = eSkill::None;
	}

	if (CheckDurationTimeSecondSkill())
	{
		m_pInteractCenter->FinishSkill(m_stSkillUsing.SecondSkillProperty);
		m_stSkillUsing.SecondSkillProperty = eSkill::None;
	}

	if (CheckDurationTimeUltimateSkill())
	{
		m_pInteractCenter->FinishSkill(m_stSkillUsing.UltimateSkillProperty);
		m_stSkillUsing.UltimateSkillProperty = eSkill::None;
	}
	UpdateMonster();
}

void CMonster::Destroy()
{
}

bool CMonster::OnEvent(eEvent eEvent, void *_value)
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
	case eEvent::DeleteTornado:
		DeleteTornado();
		break;
	case eEvent::CompleteBluePrint:
		AddBluePrintCount();
		break;
	}
	return true;
}

bool CMonster::FirstSkillTriggered()
{
	if (m_stSkillUsing.isSecondSkill || m_stSkillUsing.isUltimateSkill)
		return false;

	m_fFirstSkillConditionElapsedTime += g_pTimeManager->GetElapsedTime();

	if (m_fFirstSkillConditionElapsedTime >= m_fFirstSkillConditionTime)
	{
		m_fFirstSkillConditionElapsedTime = 0;
		return true;
	}

	return false;
}

bool CMonster::SecondSkillTriggered()
{
	if (m_stSkillUsing.isUltimateSkill)
		return false;

	if (m_fTravelDistance >= 32.0f)
		return true;

	if (m_isArrive)
		return true;

	if (m_nCombinUseCount >= 6)
		return true;

	if (m_nVendingUseCount >= 4)
		return true;

	if (m_nCrowdControlCount >= 3)
		return true;

	if (m_nThrowPartsCount >= 6)
		return true;

	if (m_nSpinPartsCount >= 6)
		return true;

	return false;
}

bool CMonster::UltimateSkillTriggered()
{
	if (m_stSkillUsing.isUltimateSkill)
		return false;

	if (m_stSkillUsing.isUltimatePartsCheck && m_pInteractCenter->CheckSpecificPartsID(m_sSpecificPartsID))
	{
		m_stSkillUsing.isUltimatePartsCheck = false;
		return true;
	}

	if (m_stSkillUsing.isUltimateBluePrintCheck && m_nBluePrintChangeCount >= 10)
	{
		m_stSkillUsing.isUltimateBluePrintCheck = false;
		g_EventManager->Detach(eEvent::CompleteBluePrint, this);
		return true;
	}

	if (m_stSkillUsing.isUltimateTimeCheck && m_pInteractCenter->GetTime() < m_fUltimateSkillConditionTime)
	{
		m_stSkillUsing.isUltimateTimeCheck = false;
		return true;
	}

	return false;
}

void CMonster::ChooseSkillCondition()
{
	SkillConditionInit();

	CRandomNumberGenerator r;
	int random = r.GenInt(0, 99);
	{
		if (random < 16)
		{
			m_eSkillCondition = eSkillCondition::TravelDistance;
			g_EventManager->Attach(eEvent::TravelDistance, this);
			m_eSecondSkillEvent = eEvent::TravelDistance;
		}
		else if (random < 30)
		{
			m_eSkillCondition = eSkillCondition::SpecificArea;
			g_EventManager->Attach(eEvent::SpecificArea, this);
			m_eSecondSkillEvent = eEvent::SpecificArea;
			m_vSpecificAreaPosition = m_pInteractCenter->SelectRandomObject();
		}
		else if (random < 48)
		{
			m_eSkillCondition = eSkillCondition::CombinUse;
			g_EventManager->Attach(eEvent::CombinUse, this);
			m_eSecondSkillEvent = eEvent::CombinUse;
		}
		else if (random < 62)
		{
			m_eSkillCondition = eSkillCondition::VendingUse;
			g_EventManager->Attach(eEvent::VendingUse, this);
			m_eSecondSkillEvent = eEvent::VendingUse;
		}
		else if (random < 74)
		{
			m_eSkillCondition = eSkillCondition::CrowdControl;
			g_EventManager->Attach(eEvent::CrowdControl, this);
			m_eSecondSkillEvent = eEvent::CrowdControl;
		}
		else if (random < 86)
		{
			m_eSkillCondition = eSkillCondition::ThrowParts;
			g_EventManager->Attach(eEvent::ThrowParts, this);
			m_eSecondSkillEvent = eEvent::ThrowParts;
		}
		else
		{
			m_eSkillCondition = eSkillCondition::SpinParts;
			g_EventManager->Attach(eEvent::SpinParts, this);
			m_eSecondSkillEvent = eEvent::SpinParts;
		}
	}

	//테스트용
	/*m_eSkillCondition = eSkillCondition::SpecificArea;
	g_EventManager->Attach(eEvent::SpecificArea, this);
	m_eSecondSkillEvent = eEvent::SpecificArea;
	m_pInteractCenter->SelectRandomObject();*/

	_DEBUG_COMMENT switch (m_eSkillCondition)
	_DEBUG_COMMENT {
	_DEBUG_COMMENT 	case eSkillCondition::TravelDistance : 
	_DEBUG_COMMENT 		cout << m_debugName << ":" << "걷기 조건" << endl;
	_DEBUG_COMMENT 	break;
	_DEBUG_COMMENT 	case eSkillCondition::SpecificArea : 
	_DEBUG_COMMENT 		cout << m_debugName << ":" << "특정지역 조건" << endl;
	_DEBUG_COMMENT 	break;
	_DEBUG_COMMENT 	case eSkillCondition::CombinUse : 
	_DEBUG_COMMENT 		cout << m_debugName << ":"<< "조합기사용 조건"<< endl;
	_DEBUG_COMMENT 	break;
	_DEBUG_COMMENT 	case eSkillCondition::VendingUse : 
	_DEBUG_COMMENT 		cout << m_debugName << ":"<< "자판기사용 조건"<< endl;
	_DEBUG_COMMENT 	break;
	_DEBUG_COMMENT 	case eSkillCondition::CrowdControl : 
	_DEBUG_COMMENT 		cout << m_debugName << ":"<< "CC걸린횟수 조건"<< endl;
	_DEBUG_COMMENT 	break;
	_DEBUG_COMMENT 	case eSkillCondition::ThrowParts : 
	_DEBUG_COMMENT 		cout << m_debugName << ":"<< "파츠던지기횟수 조건"<< endl;
	_DEBUG_COMMENT 	break;
	_DEBUG_COMMENT 	case eSkillCondition::SpinParts : 
	_DEBUG_COMMENT 		cout << m_debugName << ":"<< "파츠돌리기횟수 조건"<< endl;
	_DEBUG_COMMENT 	break;
	_DEBUG_COMMENT }
}

bool CMonster::CheckDurationTimeFirstSkill()
{
	if (!m_stSkillUsing.isFirstSkill)
		return false;

	m_fFirstSkillElapsedTime += g_pTimeManager->GetElapsedTime();

	if (m_fFirstSkillElapsedTime >= FirstSkillTime())
	{
		m_stSkillUsing.isFirstSkill = false;
		m_fFirstSkillElapsedTime = 0;
		return true;
	}
	return false;
}

bool CMonster::CheckDurationTimeSecondSkill()
{
	if (!m_stSkillUsing.isSecondSkill)
		return false;

	m_fSecondSkillElapsedTime += g_pTimeManager->GetElapsedTime();

	if (m_fSecondSkillElapsedTime >= SecondSkillTime())
	{
		m_stSkillUsing.isSecondSkill = false;
		m_fSecondSkillElapsedTime = 0;
		return true;
	}
	return false;
}

bool CMonster::CheckDurationTimeUltimateSkill()
{
	if (!m_stSkillUsing.isUltimateSkill)
		return false;

	m_fUltimateSkillElapsedTime += g_pTimeManager->GetElapsedTime();

	if (m_fUltimateSkillElapsedTime >= UltimateSkillTime())
	{
		m_stSkillUsing.isUltimateSkill = false;
		m_fUltimateSkillElapsedTime = 0;
		return true;
	}
	return false;
}

void CMonster::FinishSkill(eSkill skill)
{
	m_pInteractCenter->FinishSkill(skill);
}

void CMonster::AddObjectPosition(D3DXVECTOR3 pos)
{
	m_vecObjectPosition.push_back(pos);
}

void CMonster::AddBluePrintCount()
{
	m_nBluePrintChangeCount++;
}

void CMonster::TravelDistanceSkill(void *_value)
{
	ST_TravelDistanceEvent *data = static_cast<ST_TravelDistanceEvent *>(_value);

	m_fTravelDistance += data->fDistance;
}

void CMonster::SkillConditionInit()
{
	if (m_eSecondSkillEvent == eEvent::None)
		return;
	g_EventManager->Detach(m_eSecondSkillEvent, this);

	switch (m_eSecondSkillEvent)
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
