#pragma once
#include "CUIStar.h"
class CUISelectStarThree :
	public CUIStar
{
public:
	CUISelectStarThree(D3DXVECTOR2 vPos);
	~CUISelectStarThree();

public:
	void Setup() override;
};

