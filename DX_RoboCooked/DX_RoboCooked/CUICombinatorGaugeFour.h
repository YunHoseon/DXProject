#pragma once
#include "CUICombinatorGaugeBoard.h"
class CUICombinatorGaugeFour :
	public CUICombinatorGaugeBoard
{
public:
	CUICombinatorGaugeFour(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeFour();
	void Setup() override;
};

