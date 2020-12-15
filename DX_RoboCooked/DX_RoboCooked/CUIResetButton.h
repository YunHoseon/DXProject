#pragma once
#include "CUIButton.h"
class CUIResetButton :
	public CUIButton
{
public:
	CUIResetButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIResetButton();

	virtual void Setup() override;


};

