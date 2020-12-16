#pragma once
#include "CUIButton.h"
class CUILoseBoard :
	public CUIButton
{
public:
	CUILoseBoard();
	~CUILoseBoard();
public:
	virtual void Setup() override;
};

