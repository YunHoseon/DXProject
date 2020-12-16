#pragma once
#include "CUIButton.h"
class CUILoadingScreen :
	public CUIButton
{
public:
	CUILoadingScreen();
	~CUILoadingScreen();

	virtual void Setup() override;
};

