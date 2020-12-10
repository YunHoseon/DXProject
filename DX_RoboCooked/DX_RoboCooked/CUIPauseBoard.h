#pragma once
#include"CUIButton.h"

class CUIButton;

class CUIPauseBoard :
	public CUIButton

{
public:
	CUIPauseBoard(D3DXVECTOR2 vPos);
	~CUIPauseBoard();

public:
	virtual void Setup() override;

};

