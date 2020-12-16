#pragma once
#include "CUIButton.h"
class IInteractCenter;
class CUILoseButton :
	public CUIButton
{
private:
	IInteractCenter*	m_pInteractCenter;

public:
	CUILoseButton(IInteractCenter* pInteractCenter);
	~CUILoseButton();

public:
	virtual void Setup() override;
	bool OnEvent(eEvent eEvent, void * _value);
	void ResetGame();
};

