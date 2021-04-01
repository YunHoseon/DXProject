#pragma once
#include "CUIButton.h"
class CUIChargeBoard :
	public CUIButton
{
protected:
	D3DXVECTOR3* m_pPosition;
public:
	CUIChargeBoard(D3DXVECTOR3* pPos);
	virtual ~CUIChargeBoard();

public:
	void Setup() = 0;
};

