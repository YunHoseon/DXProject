#pragma once
#include "CUIButton.h"
class CUIClearBoard :
	public CUIButton
{
public:
	CUIClearBoard(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIClearBoard();
public:
	virtual void Setup() override;
};

