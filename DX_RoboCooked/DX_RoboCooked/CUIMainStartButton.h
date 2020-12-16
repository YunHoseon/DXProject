#pragma once
#include "CUIButton.h"
class CUIMainStartButton :
	public CUIButton
{
public:
	CUIMainStartButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIMainStartButton();

public:
	virtual void Setup() override;
};

