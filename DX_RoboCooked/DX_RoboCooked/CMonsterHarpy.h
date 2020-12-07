#pragma once
#include "CMonster.h"
class CMonsterHarpy :
	public CMonster
{
public:
	CMonsterHarpy(IInteractCenter* pInteractCenter);
	~CMonsterHarpy();

	eSkill FirstSkill() override;
	eSkill SecondSkill() override;
	eSkill UltimateSkill() override;

	FLOAT FirstSkillTime() override { return 10.0f; };
	FLOAT SecondSkillTime() override { return 10.0f; };
	FLOAT UltimateSkillTime() override { return 0.0f; };

};

