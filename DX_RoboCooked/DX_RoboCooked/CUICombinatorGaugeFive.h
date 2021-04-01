#pragma once
#include "CUIChargeBoard.h"
class CUICombinatorGaugeFive :
	public CUIChargeBoard
{
public:
	CUICombinatorGaugeFive(D3DXVECTOR3* pPos);
	~CUICombinatorGaugeFive();
	void Setup() override;
};

