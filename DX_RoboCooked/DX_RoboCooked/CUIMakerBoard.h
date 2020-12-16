#pragma once
#include "CUIButton.h"
class CUIMakerBoard :
	public CUIButton
{
public:
	CUIMakerBoard(D3DXVECTOR2 vPos);
	~CUIMakerBoard();
public:
	virtual void Setup() override;

};

