#include "stdafx.h"
#include "CMonsterMedusa.h"


CMonsterMedusa::CMonsterMedusa(IInteractCenter* pInteractCenter):CMonster(pInteractCenter)
{
	m_fFirstSkillConditionTime = 40;
}


CMonsterMedusa::~CMonsterMedusa()
{
}


eSkill CMonsterMedusa::FirstSkill()
{
	//return eSkill::SandWind;
	return eSkill::KeyLock;
}

eSkill CMonsterMedusa::SecondSkill()
{
	return eSkill::SlowMove;
}

eSkill CMonsterMedusa::UltimateSkill()
{
	return eSkill::DestroyParts;
}
