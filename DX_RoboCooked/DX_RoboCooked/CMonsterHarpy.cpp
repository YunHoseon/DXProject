#include "stdafx.h"
#include "CMonsterHarpy.h"

#include "CSkinnedMesh.h"
#include "IInteractCenter.h"
#include "CTornado.h"


CMonsterHarpy::CMonsterHarpy(IInteractCenter* pInteractCenter) :CMonster(pInteractCenter), m_pTornado(nullptr), m_pSkillAnim_2(nullptr)
{
	m_fFirstSkillConditionTime = 30.0f;
	m_fUltimateSkillConditionTime = 120.0f;
	m_sSpecificPartsID = "B03";
	m_debugName = "ÇÏÇÇ";
	ChooseSkillCondition();
	
	g_EventManager->Attach(eEvent::DeleteTornado, this);

	//m_pSkillAnim_2 = new CSkinnedMesh;
	//m_pSkillAnim_2->Load("data/model/monster", "harpy_skill_2.x");
}


CMonsterHarpy::~CMonsterHarpy()
{
	SafeDelete(m_pTornado);
}

void CMonsterHarpy::Render()
{
	if(m_pTornado)
		m_pTornado->Render();

	if (m_pSkillAnim_2)
		m_pSkillAnim_2->Render(nullptr);
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

void CMonsterHarpy::Update()
{

	if (FirstSkillTriggered())
	{
		m_stSkillUsing.FirstSkillProperty = FirstSkill();
		m_stSkillUsing.isFirstSkill = true;
		m_pInteractCenter->MonsterSkill(FirstSkill(), FirstSkillTime());

	}

	if (SecondSkillTriggered())
	{
		m_stSkillUsing.SecondSkillProperty = SecondSkill();
		m_stSkillUsing.isSecondSkill = true;
		ChooseSkillCondition();
		m_pInteractCenter->MonsterSkill(SecondSkill(), SecondSkillTime());

	}

	if (m_eSecondSkillEvent == eEvent::SpecificArea)
	{
		if (m_pInteractCenter->CheckSpecificArea())
		{
			m_isArrive = true;
		}
	}

	if (UltimateSkillTriggered())
	{
		m_stSkillUsing.UltimateSkillProperty = UltimateSkill();
		m_stSkillUsing.isUltimateSkill = true;
		m_pInteractCenter->MonsterSkill(UltimateSkill(), UltimateSkillTime());

	}

	if (CheckDurationTimeFirstSkill())
	{
		m_pInteractCenter->FinishSkill(m_stSkillUsing.FirstSkillProperty);
		m_stSkillUsing.FirstSkillProperty = eSkill::None;
	}

	if (CheckDurationTimeSecondSkill())
	{
		m_pInteractCenter->FinishSkill(m_stSkillUsing.SecondSkillProperty);
		m_stSkillUsing.SecondSkillProperty = eSkill::None;
	}

	if (CheckDurationTimeUltimateSkill())
	{
		m_pInteractCenter->FinishSkill(m_stSkillUsing.UltimateSkillProperty);
		m_stSkillUsing.UltimateSkillProperty = eSkill::None;
	}
	UpdateMonster();

}

void CMonsterHarpy::UpdateMonster()
{
	if (m_pSkillAnim_2)
		m_pSkillAnim_2->Update();
}



