#pragma once
#include "CUIButton.h"
class CUICombinatorGaugeBoard :
	public CUIButton
{
protected:
	D3DXVECTOR3* m_pPosition;
public:
	CUICombinatorGaugeBoard(D3DXVECTOR3* pPos);
	virtual ~CUICombinatorGaugeBoard();

public:
	void Setup() = 0;
};

