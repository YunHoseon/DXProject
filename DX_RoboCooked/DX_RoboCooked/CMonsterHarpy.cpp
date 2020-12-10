#include "stdafx.h"
#include "CMonsterHarpy.h"
#include "IInteractCenter.h"
#include "CTornado.h"


CMonsterHarpy::CMonsterHarpy(IInteractCenter* pInteractCenter):CMonster(pInteractCenter), m_pTornado(nullptr)
{
	m_fFirstSkillConditionTime = 30.0f;
	m_fUltimateSkillConditionTime = 120.0f;
	m_sSpecificPartsID = "B03";
	m_debugName = "ÇÏÇÇ";
	ChooseSkillCondition();
	g_EventManager->Attach(eEvent::DeleteTornado, this);
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

void CMonsterHarpy::AddForce(CActor * target)
{
	if (m_pTornado)
	{
		D3DXVECTOR3 dir(0, 0, 0);
		if (m_pTornado->Collide(target, &dir))
		{
			target->AddForce(dir * m_pTornado->GetPower() * TimeRevision);
		}
	}
}

eSkill CMonsterHarpy::SecondSkill()
{
	if (m_vecObjectPosition.empty())
		return eSkill::None;

	if(m_pTornado)
		return eSkill::Tornado;

	CRandomNumberGenerator rand;
	int index = rand.GenInt(0, m_vecObjectPosition.size() - 1);
	m_pTornado = new CTornado(m_vecObjectPosition[index]);


	return eSkill::Tornado; 
}

void CMonsterHarpy::DeleteTornado()
{
	SafeDelete(m_pTornado);
}



