#pragma once
#include "CUISelect.h"
class CUISelectUnsolved :
	public CUISelect
{
public:
	CUISelectUnsolved(D3DXVECTOR2 vPos, string chStageID, float fTime, int nPage, eBtnEvent eEvent);
	~CUISelectUnsolved();

public:
	void Setup();
	bool OnEvent(eEvent eEvent, void * _value);
};

