#pragma once
#include "CUIButton.h"
class CUICloseButton :
	public CUIButton
{
public:
	CUICloseButton(D3DXVECTOR2 vPos ,eBtnEvent btnEvent);
	~CUICloseButton();
public:
	virtual void Setup() override;
};

