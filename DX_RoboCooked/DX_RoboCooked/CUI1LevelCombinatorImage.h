#pragma once
#include "CUIButton.h"
class CUI1LevelCombinatorImage :
	public CUIButton
{
public:
	CUI1LevelCombinatorImage(D3DXVECTOR2 vPos);
	~CUI1LevelCombinatorImage();
public:
	virtual void Setup() override;
};

