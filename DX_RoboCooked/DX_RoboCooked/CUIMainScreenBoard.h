#pragma once
#include "CUIButton.h"
class CUIMainScreenBoard :
	public CUIButton
{
public:
	CUIMainScreenBoard();
	~CUIMainScreenBoard();

public:
	virtual void Setup() override;
};

