#pragma once
#include "CUIButton.h"
class CUIWarningBoard :
	public CUIButton
{
public:
	CUIWarningBoard(D3DXVECTOR2 vPos);
	~CUIWarningBoard();
public:
	virtual void Setup() override;
};

