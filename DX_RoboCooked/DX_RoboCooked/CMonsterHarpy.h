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

};

