#pragma once
#include "CUICombinatorGaugeBoard.h"
class CUICombinatorGaugeOne :
	public CUICombinatorGaugeBoard
{
public:
	CUICombinatorGaugeOne(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeOne();
	void Setup() override;
};

