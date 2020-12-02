#pragma once
#include "CEventListener.h"
#include "IInteractCenter.h"


class CCrowdControl;
class IInteractCenter;

class CMonster : public CEventListener
{
protected:
	IInteractCenter*			m_pInteractCenter;
	array<CCrowdControl*, 3>	m_arrCC;
	array<int, 3>				m_arrCCCount;
	INT							m_nSpinParts;

public:
	CMonster(IInteractCenter* pInteractCenter);
	~CMonster();
public:
	virtual void Update();
	virtual void Render();
	CCrowdControl* ChooseCC();
	virtual void OnEvent(eEvent eEvent, void* _value) override;
	virtual bool Istriggered();
	void SpinPartsSkill();
};
