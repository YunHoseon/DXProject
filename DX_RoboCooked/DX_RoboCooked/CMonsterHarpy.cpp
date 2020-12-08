#include "stdafx.h"
#include "CMonsterHarpy.h"


CMonsterHarpy::CMonsterHarpy(IInteractCenter* pInteractCenter):CMonster(pInteractCenter)
{
	m_fFirstSkillConditionTime = 30.0f;
}


CMonsterHarpy::~CMonsterHarpy()
{
}

