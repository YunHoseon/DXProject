#pragma once
#include "CUIButton.h"
class CUISelectStartButton :
	public CUIButton
{
public:
	CUISelectStartButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUISelectStartButton();

public:
	virtual void Setup() override;

};

