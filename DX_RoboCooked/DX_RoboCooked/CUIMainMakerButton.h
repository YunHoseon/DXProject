#pragma once
#include "CUIButton.h"
class CUIMainMakerButton :
	public CUIButton
{
public:
	CUIMainMakerButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIMainMakerButton();
public:
	virtual void Setup() override;
};

