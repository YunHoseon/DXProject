#include "stdafx.h"
#include "CMonsterHarpy.h"
#include "IInteractCenter.h"
#include "CTornado.h"


CMonsterHarpy::CMonsterHarpy(IInteractCenter* pInteractCenter):CMonster(pInteractCenter), m_pTornado(nullptr)
{
	m_fFirstSkillConditionTime = 30.0f;
	m_fUltimateSkillConditionTime = 120.0f;
	m_sSpecificPartsID = "B03";
}


CMonsterHarpy::~CMonsterHarpy()
{
	SafeDelete(m_pTornado);
}

void CMonsterHarpy::Render()
{
	if(m_pTornado)
		m_pTornado->Render();
}

void CMonsterHarpy::MonsterUpdate()
{
	if (m_pTornado)
	{
		m_pTornado->Update();
		m_pInteractCenter->UpdateTornado(m_pTornado);
	}
}

eSkill CMonsterHarpy::SecondSkill()
{
	if (m_vecObjectPosition.empty())
		return eSkill::None;

	CRandomNumberGenerator rand;
	int index = rand.GenInt(0, m_vecObjectPosition.size() - 1);
	m_pTornado = new CTornado(m_vecObjectPosition[index]);
	g_EventManager->Attach(eEvent::DeleteTornado, this);

	return eSkill::Tornado; 
}

void CMonsterHarpy::DeleteTornado()
{
	SafeDelete(m_pTornado);
}



