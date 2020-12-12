#pragma once
#include "CUIButton.h"
class CUILight :
	public CUIButton
{
public:
	CUILight(D3DXVECTOR2 vPos);
	~CUILight();
public:
	virtual void Setup() override;
};

