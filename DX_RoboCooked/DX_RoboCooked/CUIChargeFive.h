#pragma once
#include "CUIChargeBoard.h"
class CUIChargeFive :
	public CUIChargeBoard
{
public:
	CUIChargeFive(D3DXVECTOR3* pPos);
	~CUIChargeFive();

public:
	void Setup() override;
};

