#pragma once
#include "CUIButton.h"
class CUIControllBoard :
	public CUIButton
{
public:
	CUIControllBoard(D3DXVECTOR2 vPos);
	~CUIControllBoard();

public:
	void Setup() override;
};

