#pragma once
#include "CUIButton.h"
class CUISelectLeft :
	public CUIButton
{
public:
	CUISelectLeft(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUISelectLeft();

public:
	void Setup()override;
};

