#pragma once
#include "CUIButton.h"
class IInteractCenter;
class CUILoseButton :
	public CUIButton
{
public:
	CUILoseButton(D3DXVECTOR2 vPos, IInteractCenter* pInteractCenter);
	~CUILoseButton();

public:
	virtual void Setup() override;
	bool OnEvent(eEvent eEvent, void * _value);
	//void ResetGame();
};

