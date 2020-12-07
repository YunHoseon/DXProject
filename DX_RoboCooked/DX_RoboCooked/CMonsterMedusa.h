#pragma once
#include "CMonster.h"
class CMonsterMedusa :
	public CMonster
{
public:
	CMonsterMedusa(IInteractCenter* pInteractCenter);
	~CMonsterMedusa();

	eSkill FirstSkill() override;
	eSkill SecondSkill() override;
	eSkill UltimateSkill() override;

	FLOAT FirstSkillTime() override { return 10.0f; };
	FLOAT SecondSkillTime() override { return 10.0f; };
	FLOAT UltimateSkillTime() override { return 10.0f; };
};

