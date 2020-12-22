#pragma once
#include "CUICombinatorGaugeBoard.h"
class CUICombinatorGaugeFive :
	public CUICombinatorGaugeBoard
{
public:
	CUICombinatorGaugeFive(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeFive();
	void Setup() override;
};

