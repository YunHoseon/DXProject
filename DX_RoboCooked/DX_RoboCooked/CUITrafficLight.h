#pragma once
#include "CUIButton.h"

class IInteractCenter;

class CUITrafficLight :
	public CUIButton
{

private:
	IInteractCenter*	m_pInteractCenter;
	INT					m_nCompleteBluePrintCount;

public:
	CUITrafficLight(IInteractCenter* pInteractCenter,int nSize);
	~CUITrafficLight();

public:
	virtual void Setup() override;
	void OnEvent(eEvent eEvent, void * _value);
};

