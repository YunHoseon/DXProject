#pragma once
#include "CUIButton.h"
class CUILoseBoard :
	public CUIButton
{
public:
	CUILoseBoard(D3DXVECTOR2 vPos);
	~CUILoseBoard();
public:
	virtual void Setup() override;
};

