#pragma once
#include "CUIButton.h"
class CUIResetButton :
	public CUIButton
{
public:
	CUIResetButton(D3DXVECTOR2 vPos);
	~CUIResetButton();

	virtual void Setup() override;


};

