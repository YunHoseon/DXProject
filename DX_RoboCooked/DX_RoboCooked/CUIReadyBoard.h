#pragma once
#include "CUIButton.h"
class CUIReadyBoard :
	public CUIButton
{
public:
	CUIReadyBoard(D3DXVECTOR2 vPos);
	~CUIReadyBoard();
public:
	virtual void Setup() override;
};

