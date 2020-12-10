#pragma once
#include "CUIButton.h"
class CUICloseButton :
	public CUIButton
{
public:
	CUICloseButton(D3DXVECTOR2 vPos);
	~CUICloseButton();
public:
	virtual void Setup() override;
};

