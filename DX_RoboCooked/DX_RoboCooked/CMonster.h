#pragma once
#include "CEventListener.h"
#include "IInteractCenter.h"

class CCrowdControl;
class IInteractCenter;
class CActor;

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
	KeyReverse,
	SandWind,
	Tornado
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
	eSkill			FirstSkillProperty;
	eSkill			SecondSkillProperty;
	eSkill			UltimateSkillProperty;

	bool			isFirstSkill;
	bool			isSecondSkill;
	bool			isUltimateSkill;

	bool			isUltimatePartsCheck;
	bool			isUltimateBluePrintCheck;
	bool			isUltimateTimeCheck;

	
	
	ST_Skill():isFirstSkill(false),isSecondSkill(false),isUltimateSkill(false), isUltimatePartsCheck(true), isUltimateBluePrintCheck(true), isUltimateTimeCheck(true){}
};


class CMonster : public CEventListener
{
protected:
	IInteractCenter*			m_pInteractCenter;
	eSkillCondition				m_eSkillCondition;
	eEvent						m_eSecondSkillEvent;
	FLOAT						m_fFirstSkillConditionTime;
	FLOAT						m_fFirstSkillConditionElapsedTime;

	FLOAT						m_fFirstSkillElapsedTime;
	FLOAT						m_fSecondSkillElapsedTime;
	FLOAT						m_fUltimateSkillElapsedTime;

	FLOAT						m_fUltimateSkillConditionTime;
	ST_Skill					m_stSkillUsing;

	//조건리스트 
	FLOAT						m_fTravelDistance;//1
	BOOL						m_isArrive; //2
	INT							m_nCombinUseCount;//3
	INT							m_nVendingUseCount;//4
	INT							m_nCrowdControlCount;//5
	INT							m_nThrowPartsCount;//6
	INT							m_nSpinPartsCount;//7

	INT							m_nBluePrintChangeCount;
	string						m_sSpecificPartsID;
	vector<D3DXVECTOR3>			m_vecObjectPosition;

	//디버그용
	string						m_debugName;

public:
	CMonster(IInteractCenter* pInteractCenter);
	virtual ~CMonster();
public:
	virtual void Update();
	virtual void Render() = 0;
	virtual void Destroy();
	virtual bool OnEvent(eEvent eEvent, void* _value) override;
	virtual void AddForce(CActor* target) {};
	
	virtual eSkill FirstSkill() { return eSkill::None; };
	virtual eSkill SecondSkill() { return eSkill::None; };
	virtual eSkill UltimateSkill() { return eSkill::None; };

	virtual FLOAT FirstSkillTime() = 0;
	virtual FLOAT SecondSkillTime() = 0;
	virtual FLOAT UltimateSkillTime() = 0;
	virtual void UpdateMonster() {};



	bool CheckDurationTimeFirstSkill();
	bool CheckDurationTimeSecondSkill();
	bool CheckDurationTimeUltimateSkill();

	void FinishSkill(eSkill skill);
	void AddObjectPosition(D3DXVECTOR3 pos);
	void AddBluePrintCount();
	virtual void DeleteTornado() {};
	void ChooseSkillCondition();
public:
	void TravelDistanceSkill(void* _value);
	void ArriveSkill() { m_isArrive = true; }
	void CombinUseSkill() { m_nCombinUseCount++; }
	void VendingUseSkill() { m_nVendingUseCount++; }
	void CrowdControlSkill() { m_nCrowdControlCount++; }
	void ThrowPartsSkill() { m_nThrowPartsCount++; }
	void SpinPartsSkill(){ m_nSpinPartsCount++; }

protected:
	void SkillConditionInit();
	bool UltimateSkillTriggered();
	bool SecondSkillTriggered();
	bool FirstSkillTriggered();
};

#include "CMonsterMedusa.h"
#include "CMonsterHarpy.h"