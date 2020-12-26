#pragma once
#include "CUIButton.h"
class CUI1LevelCombination :
	public CUIButton
{
public:
	CUI1LevelCombination(D3DXVECTOR2 vPos);
	~CUI1LevelCombination();
public:
	virtual void Setup() override;
};

