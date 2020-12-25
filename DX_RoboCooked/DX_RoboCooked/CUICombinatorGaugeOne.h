#pragma once
#include "CUIChargeBoard.h"
class CUICombinatorGaugeOne :
	public CUIChargeBoard
{
public:
	CUICombinatorGaugeOne(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeOne();
	void Setup() override;
};

