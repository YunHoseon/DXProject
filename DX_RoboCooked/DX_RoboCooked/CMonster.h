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
	CastParts,
	SpinParts
};

class CMonster : public CEventListener
{
protected:
	IInteractCenter*			m_pInteractCenter;
	eSkillCondition				m_eSkillCondition;
	eEvent						m_eSkillEvent;
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
	~CMonster();
public:
	virtual void Update();
	virtual void Render();
	virtual void SkillConditionInit();
	virtual void Destroy();
	CCrowdControl* ChooseCC();
	virtual void OnEvent(eEvent eEvent, void* _value) override;
	virtual bool Istriggered();
	void ChooseSkillCondition();

	void TravelDistanceSkill(void* _value);
	void ArriveSkill() { m_isArrive = true; }
	void CombinUseSkill() { m_nCombinUseCount++; }
	void VendingUseSkill() { m_nVendingUseCount++; }
	void CrowdControlSkill() { m_nCrowdControlCount++; }
	void ThrowPartsSkill() { m_nThrowPartsCount++; }
	void SpinPartsSkill(){ m_nSpinPartsCount++; }

	
};
