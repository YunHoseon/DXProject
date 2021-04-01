#pragma once
#include "CUIChargeBoard.h"
class CUICombinatorGaugeThree :
	public CUIChargeBoard
{
public:
	CUICombinatorGaugeThree(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeThree();
	void Setup() override;
};

