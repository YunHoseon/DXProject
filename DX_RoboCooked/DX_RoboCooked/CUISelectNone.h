#pragma once
#include "CUISelect.h"
class CUISelectNone :
	public CUISelect
{
public:
	CUISelectNone(D3DXVECTOR2 vPos, string chStageID, float fTime);
	~CUISelectNone();

public: 
	void Setup();
};

