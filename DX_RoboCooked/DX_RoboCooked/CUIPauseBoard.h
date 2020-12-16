#pragma once
#include"CUIButton.h"

class CUIButton;

class CUIPauseBoard :
	public CUIButton

{
public:
	CUIPauseBoard(eBtnEvent btnEvent);
	~CUIPauseBoard();

public:
	virtual void Setup() override;

};

