#pragma once
#include "CUIButton.h"
class CUI2LevelCombinatorImage :
	public CUIButton
{
public:
	CUI2LevelCombinatorImage(D3DXVECTOR2 vPos);
	~CUI2LevelCombinatorImage();
public:
	virtual void Setup() override;
};

