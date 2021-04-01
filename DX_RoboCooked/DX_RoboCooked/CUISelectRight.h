#pragma once
#include "CUIButton.h"
class CUISelectRight :
	public CUIButton
{
public:
	CUISelectRight(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUISelectRight();

public:
	void Setup()override;
};

