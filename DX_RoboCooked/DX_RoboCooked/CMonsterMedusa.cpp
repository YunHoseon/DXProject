#include "stdafx.h"
#include "CMonsterMedusa.h"


CMonsterMedusa::CMonsterMedusa(IInteractCenter* pInteractCenter):CMonster(pInteractCenter)
{
	m_fFirstSkillConditionTime = 40.0f;
	m_fUltimateSkillConditionTime = 120.0f;
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


