#pragma once
#include "CMonster.h"
class CMonsterMedusa :
	public CMonster
{
public:
	CMonsterMedusa(IInteractCenter* pInteractCenter);
	~CMonsterMedusa();

	void Render() override;

	eSkill FirstSkill() override { return eSkill::KeyLock; }
	eSkill SecondSkill() override { return eSkill::SlowMove; }
	eSkill UltimateSkill() override { return eSkill::DestroyParts; }

	FLOAT FirstSkillTime() override { return 3.0f; };
	FLOAT SecondSkillTime() override { return 5.0f; };
	FLOAT UltimateSkillTime() override { return 5.0f; };
};

