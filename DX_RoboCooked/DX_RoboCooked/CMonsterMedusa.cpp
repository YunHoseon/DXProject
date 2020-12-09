#include "stdafx.h"
#include "CMonsterMedusa.h"


CMonsterMedusa::CMonsterMedusa(IInteractCenter* pInteractCenter):CMonster(pInteractCenter)
{
	m_fFirstSkillConditionTime = 40.0f;
	m_fUltimateSkillConditionTime = 120.0f;
}


CMonsterMedusa::~CMonsterMedusa()
{
}


