#pragma once
#include "CUIButton.h"
class CUIMainButton :
	public CUIButton
{
public:
	CUIMainButton(D3DXVECTOR2 vPos);
	~CUIMainButton();
public:
	virtual void Setup() override;
};

