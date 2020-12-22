#pragma once
#include "CUICombinatorGaugeBoard.h"
class CUICombinatorGaugeTwo :
	public CUICombinatorGaugeBoard
{
public:
	CUICombinatorGaugeTwo(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeTwo();
	void Setup() override;
};

