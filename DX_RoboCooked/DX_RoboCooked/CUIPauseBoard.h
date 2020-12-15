#pragma once
#include"CUIButton.h"

class CUIButton;

class CUIPauseBoard :
	public CUIButton

{
public:
	CUIPauseBoard(D3DXVECTOR2 vPos, eBtnEvent btnEvent);
	~CUIPauseBoard();

public:
	virtual void Setup() override;

};

