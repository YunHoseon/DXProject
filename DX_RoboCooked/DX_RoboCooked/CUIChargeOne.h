#pragma once
#include "CUIChargeBoard.h"
class CUIChargeOne :
	public CUIChargeBoard
{
public:
	CUIChargeOne(D3DXVECTOR3* pPos);
	~CUIChargeOne();

public:
	void Setup() override;
};

