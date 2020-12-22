#pragma once
#include "CUISelect.h"
class CUISelectSolved :
	public CUISelect
{
public:
	CUISelectSolved(D3DXVECTOR2 vPos ,ST_GameData data , eBtnEvent eEvent);
	~CUISelectSolved();

public:
	void Setup() override;
	bool OnEvent(eEvent eEvent, void * _value);
};

