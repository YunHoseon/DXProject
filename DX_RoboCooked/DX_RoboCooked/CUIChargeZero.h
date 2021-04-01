#pragma once
#include "CUIChargeBoard.h"
class CUIChargeZero :
	public CUIChargeBoard
{
public:
	CUIChargeZero(D3DXVECTOR3* pPos);
	~CUIChargeZero();

public:
	void Setup() override;
};

