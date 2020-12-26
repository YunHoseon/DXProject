#pragma once
#include "CUIButton.h"

class CUI2LevelCombination :
	public CUIButton
{
	string	m_sPartsID;
public:
	CUI2LevelCombination(D3DXVECTOR2 vPos , string sPartsID);
	~CUI2LevelCombination();
public:
	void Setup() override;

};

