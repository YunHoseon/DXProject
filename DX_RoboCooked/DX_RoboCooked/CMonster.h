#pragma once
#include "CEventListener.h"
#include "IInteractCenter.h"

class CCrowdControl;
class IInteractCenter;

enum class eSkillCondition
{
	TravelDistance,
	SpecificArea,
	CombinUse,
	VendingUse,
	CrowdControl,
	ThrowParts,
	SpinParts
};

enum class eSkill
{
	None,
	KeyLock,
	SlowMove,
	DestroyParts,
	KeyRevers,
	SandWind,
	Flurry
};

enum class eSkillLevel
{
	None,
	One,
	Two,
	Ultimate
};

struct ST_Skill
{
	eSkill		 SkillProperty;
	eSkillLevel	 SkillLevel;
	
	ST_Skill():SkillProperty(eSkill::None), SkillLevel(eSkillLevel::None){}
};


class CMonster : public CEventListener
{
protected:
	IInteractCenter*			m_pInteractCenter;
	eSkillCondition				m_eSkillCondition;
	eEvent						m_eSkillEvent;
	FLOAT						m_fFirstSkillCoolDownTime;
	FLOAT						m_fFirstSkillElapsedTime;
	ST_Skill					m_stSkillUsing;

	//조건리스트 
	FLOAT						m_fTravelDistance;//1
	BOOL						m_isArrive; //2
	INT							m_nCombinUseCount;//3
	INT							m_nVendingUseCount;//4
	INT							m_nCrowdControlCount;//5
	INT							m_nThrowPartsCount;//6
	INT							m_nSpinPartsCount;//7

public:
	CMonster(IInteractCenter* pInteractCenter);
	virtual ~CMonster();
public:
	virtual void Update();
	virtual void Render();
	virtual void Destroy();
	virtual void OnEvent(eEvent eEvent, void* _value) override;
	
	virtual eSkill FirstSkill() { return eSkill::None; };
	virtual eSkill SecondSkill() { return eSkill::None; };
	virtual eSkill UltimateSkill() { return eSkill::None; };



	void ChooseSkillCondition();




	void SetSkillProperty(eSkill skill) { m_stSkillUsing.SkillProperty = skill; }
public:
	void TravelDistanceSkill(void* _value);
	void ArriveSkill() { m_isArrive = true; }
	void CombinUseSkill() { m_nCombinUseCount++; }
	void VendingUseSkill() { m_nVendingUseCount++; }
	void CrowdControlSkill() { m_nCrowdControlCount++; }
	void ThrowPartsSkill() { m_nThrowPartsCount++; }
	void SpinPartsSkill(){ m_nSpinPartsCount++; }

private:
	void SkillConditionInit();
	bool SecondSkillTriggered();
	bool FirstSkillTriggered();
};
