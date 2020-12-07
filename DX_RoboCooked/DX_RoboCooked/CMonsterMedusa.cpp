#include "stdafx.h"
#include "CMonsterMedusa.h"


CMonsterMedusa::CMonsterMedusa(IInteractCenter* pInteractCenter):CMonster(pInteractCenter)
{
	m_fFirstSkillCoolDownTime = 40;
}


CMonsterMedusa::~CMonsterMedusa()
{
}


eSkill CMonsterMedusa::FirstSkill()
{
	return eSkill::DestroyParts;
	//return eSkill::KeyLock;
}

eSkill CMonsterMedusa::SecondSkill()
{
	return eSkill::SlowMove;
}

eSkill CMonsterMedusa::UltimateSkill()
{
	return eSkill::DestroyParts;
}
