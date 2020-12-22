#pragma once
#include "CUICombinatorGaugeBoard.h"
class CUICombinatorGaugeThree :
	public CUICombinatorGaugeBoard
{
public:
	CUICombinatorGaugeThree(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeThree();
	void Setup() override;
};

