#pragma once
#include "CUIStar.h"
class CUIStarThree :
	public CUIStar
{
public:
	CUIStarThree(D3DXVECTOR2 vPos);
	~CUIStarThree();

public:
	void Setup() override;
};

