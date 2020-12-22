#pragma once
#include "CUIStar.h"
class CUISelectStarOne :
	public CUIStar
{
public:
	CUISelectStarOne(D3DXVECTOR2 vPos);
	~CUISelectStarOne();

public:
	void Setup() override;
};

