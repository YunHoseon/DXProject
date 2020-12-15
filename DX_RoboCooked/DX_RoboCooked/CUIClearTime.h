#pragma once
#include "CUIButton.h"
class CUIClearTime :
	public CUIButton
{
public:
	CUIClearTime(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIClearTime();

public:
	virtual void Setup();
};

