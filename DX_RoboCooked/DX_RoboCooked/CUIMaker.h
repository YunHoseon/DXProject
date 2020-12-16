#pragma once
#include "CUIButton.h"
class CUIMaker :
	public CUIButton
{
public:
	CUIMaker();
	~CUIMaker();

public:
	virtual void Setup() override;
	bool OnEvent(eEvent eEvent, void * _value);
};

