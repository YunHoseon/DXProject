#pragma once
#include "CUIChargeBoard.h"
class CUICombinatorGaugeFour :
	public CUIChargeBoard
{
public:
	CUICombinatorGaugeFour(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeFour();
	void Setup() override;
};

