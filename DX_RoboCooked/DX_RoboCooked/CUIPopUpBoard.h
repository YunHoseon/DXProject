#pragma once
#include "CUIButton.h"
class CUIPopUpBoard :
	public CUIButton
{
public:
	CUIPopUpBoard(D3DXVECTOR2 vPos);
	~CUIPopUpBoard();

public:
	void Setup()override;
};

