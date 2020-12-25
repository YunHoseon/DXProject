#pragma once
#include "CUIChargeBoard.h"
class CUICombinatorGaugeZero :
	public CUIChargeBoard
{
public:
	CUICombinatorGaugeZero(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeZero();
	void Setup() override;
};

