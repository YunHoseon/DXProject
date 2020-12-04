#pragma once
#include "CMonster.h"
class CMonsterHarpy :
	public CMonster
{
public:
	CMonsterHarpy(IInteractCenter* pInteractCenter);
	~CMonsterHarpy();

	CCrowdControl* ChooseCC() override;
	eSkill FirstSkill() override;
	eSkill SecondSkill() override;
	eSkill UltimateSkill() override;

};

