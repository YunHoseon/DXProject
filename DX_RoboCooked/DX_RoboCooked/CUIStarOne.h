#pragma once
#include "CUIStar.h"
class CUIStarOne :
	public CUIStar
{
public:
	CUIStarOne(D3DXVECTOR2 vPos);
	~CUIStarOne();

public:
	void Setup() override;
};

