#pragma once
#include "CMonster.h"
class CMonsterMedusa :
	public CMonster
{
public:
	CMonsterMedusa(IInteractCenter* pInteractCenter);
	~CMonsterMedusa();

	CCrowdControl* ChooseCC() override;
	eSkill FirstSkill() override;
	eSkill SecondSkill() override;
	eSkill UltimateSkill() override;
};

