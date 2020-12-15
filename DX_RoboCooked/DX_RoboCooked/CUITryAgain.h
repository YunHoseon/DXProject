#pragma once
#include "CUIButton.h"
class CUITryAgain :
	public CUIButton
{
public:
	CUITryAgain(D3DXVECTOR2 vPos);
	~CUITryAgain();

public:
	void Setup() override;
};

