#pragma once
#include "CMonster.h"
class CTornado;

class CMonsterHarpy :
	public CMonster
{
private:
	CTornado*		m_pTornado;
public:
	CMonsterHarpy(IInteractCenter* pInteractCenter);
	~CMonsterHarpy();

public:
	void Render() override;
	void MonsterUpdate() override;

	eSkill FirstSkill() override { return eSkill::KeyRevers; }
	eSkill SecondSkill() override;
	eSkill UltimateSkill() override { return eSkill::SandWind; }

	FLOAT FirstSkillTime() override { return 5.0f; };
	FLOAT SecondSkillTime() override { return 7.0f; };
	FLOAT UltimateSkillTime() override { return 10.0f; };

	void DeleteTornado() override;

};

