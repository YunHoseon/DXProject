#pragma once
#include "CUIChargeBoard.h"
class CUICombinatorGaugeTwo :
	public CUIChargeBoard
{
public:
	CUICombinatorGaugeTwo(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeTwo();
	void Setup() override;
};

