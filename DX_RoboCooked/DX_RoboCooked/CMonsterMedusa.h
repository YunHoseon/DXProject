#pragma once
#include "CMonster.h"
#include "CPartsDestroyer.h"

class CMonsterMedusa :
	public CMonster
{
private:
	D3DXVECTOR3		m_nDestroyPartsPosition;
	CPartsDestroyer m_cPartsDestroyer;
public:
	CMonsterMedusa(IInteractCenter* pInteractCenter);
	~CMonsterMedusa();

	void Render() override;
	void UpdateMonster() override;

	eSkill FirstSkill() override { return eSkill::KeyLock; }
	eSkill SecondSkill() override { return eSkill::SlowMove; }
	eSkill UltimateSkill() override;

	FLOAT FirstSkillTime() override { return 3.0f; };
	FLOAT SecondSkillTime() override { return 5.0f; };
	FLOAT UltimateSkillTime() override { return 5.0f; };
};

