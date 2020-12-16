#pragma once
#include "CUIButton.h"
class CUIMainEndButton :
	public CUIButton
{
public:
	CUIMainEndButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIMainEndButton();
public:
	virtual void Setup() override;
};

