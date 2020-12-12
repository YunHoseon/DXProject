#pragma once
#include "CUIButton.h"

class IInteractCenter;
class CUITrafficLightBoard;

class CUITrafficLight :
	public CUIButton
{

private:
	IInteractCenter*			m_pInteractCenter;
	CUITrafficLightBoard*		m_pLightBoard;
	INT							m_nCompleteBluePrintCount;

public:
	CUITrafficLight(IInteractCenter* pInteractCenter,int nSize);
	~CUITrafficLight();

public:
	virtual void Setup() override;
	void OnEvent(eEvent eEvent, void * _value);
	void AddCompleteBluePrintCount() 
	{
		m_nCompleteBluePrintCount++; 
		if (m_nCompleteBluePrintCount == 6)
			m_nCompleteBluePrintCount = 5;
	}
	void removeCompleteBluePrintCount()
	{ 
		m_nCompleteBluePrintCount--; 
		if (m_nCompleteBluePrintCount == -1)
			m_nCompleteBluePrintCount = 0;
	}
};

