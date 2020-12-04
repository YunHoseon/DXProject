#include "stdafx.h"
#include "CMonsterHarpy.h"


CMonsterHarpy::CMonsterHarpy(IInteractCenter* pInteractCenter):CMonster(pInteractCenter)
{
	m_fFirstSkillCoolDownTime = 30;
}


CMonsterHarpy::~CMonsterHarpy()
{
}

CCrowdControl * CMonsterHarpy::ChooseCC()
{
	return nullptr;
}

eSkill CMonsterHarpy::FirstSkill()
{
	return eSkill::CrowdControl;
}

eSkill CMonsterHarpy::SecondSkill()
{
	return eSkill::CCObjectMake;
}

eSkill CMonsterHarpy::UltimateSkill()
{
	return eSkill::CrowdControl;
}
