#pragma once
#include "CUIButton.h"
class CUISubWhiteboard :
	public CUIButton
{
public:
	CUISubWhiteboard(D3DXVECTOR2 vPos);
	~CUISubWhiteboard();

	virtual void Setup() override;
};

