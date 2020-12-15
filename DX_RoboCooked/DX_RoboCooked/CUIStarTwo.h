#pragma once
#include "CUIStar.h"
class CUIStarTwo :
	public CUIStar
{
public:
	CUIStarTwo(D3DXVECTOR2 vPos);
	~CUIStarTwo();

public:
	void Setup() override;
};

