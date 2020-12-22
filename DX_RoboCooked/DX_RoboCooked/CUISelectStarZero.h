#pragma once
#include "CUIStar.h"
class CUISelectStarZero :
	public CUIStar
{
public:
	CUISelectStarZero(D3DXVECTOR2 vPos);
	~CUISelectStarZero();

public:
	void Setup() override;
};

