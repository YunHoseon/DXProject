#pragma once
#include "CUISelect.h"
class CUISelectUnsolved :
	public CUISelect
{
public:
	CUISelectUnsolved(D3DXVECTOR2 vPos, ST_GameData data);
	~CUISelectUnsolved();

public:
	void Setup();
	bool OnEvent(eEvent eEvent, void * _value);
};

