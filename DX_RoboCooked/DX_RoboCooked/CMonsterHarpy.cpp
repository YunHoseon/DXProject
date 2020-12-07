#include "stdafx.h"
#include "CMonsterHarpy.h"


CMonsterHarpy::CMonsterHarpy(IInteractCenter* pInteractCenter):CMonster(pInteractCenter)
{
	m_fFirstSkillConditionTime = 30;
}


CMonsterHarpy::~CMonsterHarpy()
{
}

eSkill CMonsterHarpy::FirstSkill()
{
	return eSkill::KeyRevers;
}

eSkill CMonsterHarpy::SecondSkill()
{
	return eSkill::SandWind;
}

eSkill CMonsterHarpy::UltimateSkill()
{
	return eSkill::Tornado;
}
