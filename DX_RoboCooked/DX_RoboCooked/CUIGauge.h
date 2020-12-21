#pragma once
#include "CUIButton.h"
class CUIGauge :
	public CUIButton
{
public:
	CUIGauge(D3DXVECTOR3* vPos);
	~CUIGauge();
public:
	virtual void Setup() override;
};

