#pragma once
#include "CUIButton.h"
class CUIStartButton :
	public CUIButton
{
public:
	CUIStartButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIStartButton();

public:
	virtual void Setup() override;

};

