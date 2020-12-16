#pragma once
#include "CUIButton.h"
class CUIControllBoard :
	public CUIButton
{
public:
	CUIControllBoard();
	~CUIControllBoard();

public:
	void Setup() override;
};

