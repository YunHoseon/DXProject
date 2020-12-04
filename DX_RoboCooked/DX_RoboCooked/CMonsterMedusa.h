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
};

