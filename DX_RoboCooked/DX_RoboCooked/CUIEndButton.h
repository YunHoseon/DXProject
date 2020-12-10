#pragma once
#include "CUIButton.h"
class CUIEndButton :
	public CUIButton
{
public:
	CUIEndButton(D3DXVECTOR2 vPos);
	~CUIEndButton();

public:
	virtual void Setup() override;

};

