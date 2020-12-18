#pragma once
#include "CUIChargeBoard.h"
class CUIChargeFour :
	public CUIChargeBoard
{
public:
	CUIChargeFour(D3DXVECTOR3* pPos);
	~CUIChargeFour();
public:
	void Setup() override;
};

