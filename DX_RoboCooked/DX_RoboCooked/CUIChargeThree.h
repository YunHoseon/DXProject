#pragma once
#include "CUIChargeBoard.h"
class CUIChargeThree :
	public CUIChargeBoard
{
public:
	CUIChargeThree(D3DXVECTOR3* pPos);
	~CUIChargeThree();

public:
	void Setup() override;
};

