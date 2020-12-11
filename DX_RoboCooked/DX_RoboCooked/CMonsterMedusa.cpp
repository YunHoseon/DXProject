#include "stdafx.h"
#include "CMonsterMedusa.h"
#include "CSphereCollision.h"


CMonsterMedusa::CMonsterMedusa(IInteractCenter* pInteractCenter):CMonster(pInteractCenter), m_nDestroyPartsPosition(0,0,0)
{
	m_fFirstSkillConditionTime = 40.0f;
	m_fUltimateSkillConditionTime = 280.0f;
	m_sSpecificPartsID = "B04";
	m_debugName = "¸ÞµÎ»ç";
	ChooseSkillCondition();
}


CMonsterMedusa::~CMonsterMedusa()
{
}

void CMonsterMedusa::Render()
{
}

void CMonsterMedusa::UpdateMonster()
{
	if (m_stSkillUsing.isUltimateSkill)
	{
		m_pInteractCenter->MedusaUlt(m_nDestroyPartsPosition);
	}
}

eSkill CMonsterMedusa::UltimateSkill()
{
	m_nDestroyPartsPosition = m_pInteractCenter->GetRandomPartsPosition();
	return eSkill::DestroyParts;
}


