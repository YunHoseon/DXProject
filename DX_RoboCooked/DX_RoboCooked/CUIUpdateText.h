#pragma once
#include "CUIButton.h"
class CUIUpdateText :
	public CUIButton
{
public:
	CUIUpdateText(D3DXVECTOR2 vPos);
	~CUIUpdateText();

public:
	void Setup() override;
};

