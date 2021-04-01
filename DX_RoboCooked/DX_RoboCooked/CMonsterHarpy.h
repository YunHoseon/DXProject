#pragma once
#include "CMonster.h"
#include "CUIHeart.h"
#include "CUIWind.h"
class CHarpyWing;
class CTornado;


class CMonsterHarpy :
	public CMonster
{
private:
	CTornado*		m_pTornado;

	vector<CHarpyWing*>	m_vecSkillAnim_2;
	CUIHeart			m_cSkillAnim_1;
	CUIWind				m_cSkillAnim_Ultimate;

	int				m_nWindDir;
public:
	CMonsterHarpy(IInteractCenter* pInteractCenter);
	~CMonsterHarpy();

public:
	void Render() override;
	void AddForce(CActor* target) override;

	eSkill FirstSkill() override
	{
		g_SoundManager->PlaySFX("heartbeat");
		return eSkill::KeyReverse;
	}
	eSkill SecondSkill() override;
	eSkill UltimateSkill() override
	{ 
		g_SoundManager->PlaySFX("tornado");
		return eSkill::SandWind; 
	}

	FLOAT FirstSkillTime() override { return 5.0f; };
	FLOAT SecondSkillTime() override { return 7.0f; };
	FLOAT UltimateSkillTime() override { return 10.0f; };

	void DeleteTornado() override;

	void Update() override;
	void UpdateMonster() override;
};

