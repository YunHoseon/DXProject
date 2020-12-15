#pragma once
#include "CUIStar.h"
class CUIStarZero :
	public CUIStar
{
public:
	CUIStarZero(D3DXVECTOR2 vPos);
	~CUIStarZero();

public:
	void Setup() override;
};

