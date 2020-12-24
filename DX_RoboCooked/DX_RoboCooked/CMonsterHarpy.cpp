#include "stdafx.h"
#include "CMonsterHarpy.h"

#include "CHarpyWing.h"
#include "IInteractCenter.h"
#include "CTornado.h"

CMonsterHarpy::CMonsterHarpy(IInteractCenter *pInteractCenter) : CMonster(pInteractCenter), m_pTornado(nullptr), m_nWindDir(1)
{
	m_fFirstSkillConditionTime = 30.0f;
	m_fUltimateSkillConditionTime = 120.0f;
	//m_fUltimateSkillConditionTime = 290.0f;
	m_sSpecificPartsID = "B03";
	m_debugName = "harpy";
	ChooseSkillCondition();
	m_vecSkillAnim_2.resize(2);
	g_EventManager->Attach(eEvent::DeleteTornado, this);
	m_vecSkillAnim_2[0] = new CHarpyWing_L;
	m_vecSkillAnim_2[1] = new CHarpyWing_R;
}

CMonsterHarpy::~CMonsterHarpy()
{
	SafeDelete(m_pTornado);
	for (vector<CHarpyWing *>::value_type p : m_vecSkillAnim_2)
	{
		SafeDelete(p);
	}
}

void CMonsterHarpy::Render()
{
	if (m_pTornado)
		m_pTornado->Render();
	if (m_stSkillUsing.isFirstSkill)
	{
		m_cSkillAnim_1.Render();
	}
	if (m_stSkillUsing.isSecondSkill)
	{
		m_vecSkillAnim_2[0]->Render();
		m_vecSkillAnim_2[1]->Render();
	}
	if (m_stSkillUsing.isUltimateSkill)
	{
		m_cSkillAnim_Ultimate.Render();
	}
}

void CMonsterHarpy::AddForce(CActor *target)
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

	if (m_pTornado)
		return eSkill::Tornado;

	g_SoundManager->PlaySFX("wind");

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

		m_cSkillAnim_1.SetAnimation();
	}

	if (SecondSkillTriggered())
	{
		m_stSkillUsing.SecondSkillProperty = SecondSkill();
		m_stSkillUsing.isSecondSkill = true;
		ChooseSkillCondition();
		m_pInteractCenter->MonsterSkill(SecondSkill(), SecondSkillTime());

		m_vecSkillAnim_2[0]->SetAnimation();
		m_vecSkillAnim_2[1]->SetAnimation();
	}

	if (m_eSecondSkillEvent == eEvent::SpecificArea)
	{
		if (m_pInteractCenter->CheckDistanceToSelectedObject(m_vSpecificAreaPosition))
		{
			m_isArrive = true;
		}
	}

	if (UltimateSkillTriggered())
	{
		CRandomNumberGenerator r;
		m_nWindDir = r.GenInt(0, 1) ? -1 : 1;
		m_stSkillUsing.UltimateSkillProperty = UltimateSkill();
		m_stSkillUsing.isUltimateSkill = true;
		m_pInteractCenter->MonsterSkill(UltimateSkill(), m_nWindDir);

		m_cSkillAnim_Ultimate.SetAnimation(m_nWindDir);
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
	if (m_stSkillUsing.isFirstSkill)
	{
		m_cSkillAnim_1.Update();
	}
	if (m_stSkillUsing.isSecondSkill)
	{
		m_vecSkillAnim_2[0]->Update();
		m_vecSkillAnim_2[1]->Update();
	}
	if (m_stSkillUsing.isUltimateSkill)
	{
		m_cSkillAnim_Ultimate.Update();
	}
}
