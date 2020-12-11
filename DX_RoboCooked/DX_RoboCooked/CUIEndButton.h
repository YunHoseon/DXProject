#pragma once
#include "CUIButton.h"
class CUIEndButton :
	public CUIButton
{
public:
	CUIEndButton(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIEndButton();

public:
	virtual void Setup() override;

};

