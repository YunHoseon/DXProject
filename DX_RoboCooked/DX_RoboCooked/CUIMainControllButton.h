#pragma once
#include "CUIButton.h"
class CUIMainControllButton :
	public CUIButton
{
public:
	CUIMainControllButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIMainControllButton();
public:
	virtual void Setup() override;
};

