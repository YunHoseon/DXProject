#pragma once
#include "CUIStar.h"
class CUISelectStarTwo :
	public CUIStar
{
public:
	CUISelectStarTwo(D3DXVECTOR2 vPos);
	~CUISelectStarTwo();

public:
	void Setup() override;
};

