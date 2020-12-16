#pragma once
#include "CUIButton.h"
class CUIControll :
	public CUIButton
{
public:
	CUIControll();
	~CUIControll();

public:
	void Setup() override;
	bool OnEvent(eEvent eEvent, void * _value);
};

