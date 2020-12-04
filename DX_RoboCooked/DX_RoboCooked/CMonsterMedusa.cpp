#include "stdafx.h"
#include "CMonsterMedusa.h"


CMonsterMedusa::CMonsterMedusa(IInteractCenter* pInteractCenter):CMonster(pInteractCenter)
{
	m_fFirstSkillCoolDownTime = 40;
}


CMonsterMedusa::~CMonsterMedusa()
{
}

CCrowdControl * CMonsterMedusa::ChooseCC()
{
	return nullptr;
}

eSkill CMonsterMedusa::FirstSkill()
{
	return eSkill::CrowdControl;
}

eSkill CMonsterMedusa::SecondSkill()
{
	return eSkill::CrowdControl;
}

eSkill CMonsterMedusa::UltimateSkill()
{
	return eSkill::PartsDestroy;
}
