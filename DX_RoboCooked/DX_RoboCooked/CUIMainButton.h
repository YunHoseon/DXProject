#pragma once
#include "CUIButton.h"
class CUIMainButton :
	public CUIButton
{
public:
	CUIMainButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIMainButton();
public:
	virtual void Setup() override;
};

