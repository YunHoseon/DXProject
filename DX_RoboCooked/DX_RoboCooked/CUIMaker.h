#pragma once
#include "CUIButton.h"
class CUIMaker :
	public CUIButton
{
public:
	CUIMaker(D3DXVECTOR2 vPos);
	~CUIMaker();

public:
	virtual void Setup() override;
	bool OnEvent(eEvent eEvent, void * _value);
};

