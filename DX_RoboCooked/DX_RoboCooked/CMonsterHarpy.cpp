#include "stdafx.h"
#include "CMonsterHarpy.h"
#include "IInteractCenter.h"


CMonsterHarpy::CMonsterHarpy(IInteractCenter* pInteractCenter):CMonster(pInteractCenter)
{
	m_fFirstSkillConditionTime = 30.0f;
}


CMonsterHarpy::~CMonsterHarpy()
{
}

eSkill CMonsterHarpy::SecondSkill()
{
	if (m_vecObjectPosition.empty())
		return eSkill::None;

	CRandomNumberGenerator rand;
	int index = rand.GenInt(0, m_vecObjectPosition.size() - 1);

	m_pInteractCenter->SetTornado(m_vecObjectPosition[index]);
	return eSkill::Tornado; 
}



