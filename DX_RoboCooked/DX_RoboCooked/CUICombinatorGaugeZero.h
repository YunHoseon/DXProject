#pragma once
#include "CUICombinatorGaugeBoard.h"
class CUICombinatorGaugeZero :
	public CUICombinatorGaugeBoard
{
public:
	CUICombinatorGaugeZero(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeZero();
	void Setup() override;
};

