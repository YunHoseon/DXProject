#pragma once
#include "CUIChargeBoard.h"
class CUIChargeTwo :
	public CUIChargeBoard
{
public:
	CUIChargeTwo(D3DXVECTOR3* pPos);
	~CUIChargeTwo();

public:
	void Setup() override;
};

