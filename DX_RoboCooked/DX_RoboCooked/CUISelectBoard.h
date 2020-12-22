#pragma once
#include "CUIButton.h"
class CUISelectBoard :
	public CUIButton
{
public:
	CUISelectBoard(D3DXVECTOR2 vPos ,string sText);
	~CUISelectBoard();

public:
	void Setup() override;

};

