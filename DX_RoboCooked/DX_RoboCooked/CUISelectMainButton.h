#pragma once
#include "CUIButton.h"
class CUISelectMainButton :
	public CUIButton
{
public:
	CUISelectMainButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUISelectMainButton();
	void Setup() override;
};

